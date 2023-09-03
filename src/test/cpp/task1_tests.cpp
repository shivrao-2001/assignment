/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2021
 *
 * @file      google_test_runner.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation template.
 */

#include "csc232.h"
#include "gtest/gtest.h"

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
    static int possiblePoints { 0 };
    static int earnedPoints { 0 };
    static const int MAX_CORRECTNESS_PTS { 3 };

    /**
     * @brief Base test fixture that sets up grading for this assignment.
     */
    class CSC232BaseTestFixture : public ::testing::Test
    {
    public:
        CSC232BaseTestFixture() : buffer{std::stringstream{}}, sbuf{nullptr} {
            // Intentionally empty
        }

    protected:
        void SetUp ( ) override
        {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            // Redirect cout to our stringstream buffer or any other ostream
            sbuf = std::cout.rdbuf( );
            std::cout.rdbuf( buffer.rdbuf( ));

            AdditionalSetup( );

            possiblePoints += 1;
        }

        void TearDown ( ) override
        {
            // When done redirect cout to its old self
            std::cout.rdbuf( sbuf );
            sbuf = nullptr;

            AdditionalTearDown( );

            if ( !HasFailure( ))
            {
                earnedPoints += 1;
            }
        }

        virtual void AdditionalSetup ( )
        {
            /* template method for any customized additional setup */
        }

        virtual void AdditionalTearDown ( )
        {
            /* template method for any customized additional setup */
        }

        // Reusable objects for each unit test in this test fixture and any of its children
        std::stringstream buffer;
        std::streambuf* sbuf;
        /*
         * With the above in place, you can now have tests on output statements 
         * like this:
         * 
         * <some function call or executable that inserts info into output stream...>
         * const std::string expected{ "1/1/1902\n" }; // what you expect to have been inserted
         * const std::string actual{ buffer.str( ) };  // what was actually inserted
         * EXPECT_EQ( expected, actual );
         */
    };

    class Task1TestFixture : public CSC232BaseTestFixture
    {
        protected:
        int EXPECTED_ONE_D_ARRAY_SIZE{ 5 };

    };

    TEST_F( Task1TestFixture, TaskIsReadyForEvaluation )
    {
        const char* filename   = "csc232.h";
        std::ifstream input_stream{ filename, std::ios::in };
        if (!input_stream)
        {
            FAIL() << "Header file could not be opened.";
        }
        const char* search_string = "TEST_TASK1 TRUE";
        // Read the entire file into memory
        std::string file_contents;
        std::string current_line;
        while (getline( input_stream, current_line ))
            file_contents += current_line + '\n';
        input_stream.close();
        size_t pos = file_contents.find(search_string);
        EXPECT_TRUE(static_cast<int>(pos) > 0);
        if (HasFailure())
        {
            cerr << "Task is not ready for evaluation. ";
            cerr << "It appears that you have not toggled TEST_TASK1 to TRUE.\n";
        }
    }
#if TEST_TASK1
    TEST_F( Task1TestFixture, ValidateConstantDeclaration )
    {
        EXPECT_EQ( EXPECTED_ONE_D_ARRAY_SIZE, ROSTER_SIZE );
    }

    TEST_F( Task1TestFixture, ValidateOneDimensionalArrayDeclaration )
    {
        const char* filename   = "csc232.h";
        std::ifstream input_stream{ filename, std::ios::in };
        if (!input_stream)
        {
            FAIL() << "Header file could not be opened.";
        }
        const char* search_string = "testGrades";
        // Read the entire file into memory
        std::string file_contents;
        std::string current_line;
        while (getline( input_stream, current_line ))
            file_contents += current_line + '\n';
        input_stream.close();
        size_t pos = file_contents.find(search_string);
        EXPECT_TRUE(static_cast<int>(pos) > 0);
        if (HasFailure())
        {
            cerr << "Task has failed validation. ";
            cerr << "It appears that you have not named the one-dimensional array correctly as outlined in TODO 1.2.\n";
        }
    }

    TEST_F( Task1TestFixture, ValidateTwoDimensionalArrayDeclaration)
    {
        const char* filename   = "csc232.h";
        std::ifstream input_stream{ filename, std::ios::in };
        if (!input_stream)
        {
            FAIL() << "Header file could not be opened.";
        }
        const char* search_string = "gradeBook";
        // Read the entire file into memory
        std::string file_contents;
        std::string current_line;
        while (getline( input_stream, current_line ))
            file_contents += current_line + '\n';
        input_stream.close();
        size_t pos = file_contents.find(search_string);
        EXPECT_TRUE(static_cast<int>(pos) > 0);
        if (HasFailure())
        {
            cerr << "Task has failed validation. ";
            cerr << "It appears that you have not named the twl-dimensional array correctly as outlined in TODO 1.4.\n";
        }
    }
#endif

} // end namespace

int main ( int argc, char** argv )
{
    ::testing::InitGoogleTest( &argc, argv );
    int result { RUN_ALL_TESTS( ) };
    std::cout << std::fixed << std::setprecision( 2 );
    std::cout << "\n\n";
    std::cout << std::left << std::setw( 21 ) << "Earned Points:"
              << std::right << std::setw( 5 ) << static_cast<double>(csc232::earnedPoints) << std::endl;
    std::cout << std::left << std::setw( 21 ) << "Possible Points:"
              << std::right << std::setw( 5 ) << static_cast<double>(csc232::possiblePoints) << std::endl;
    double percentCorrect { static_cast<double>(csc232::earnedPoints) / csc232::possiblePoints };
    double correctnessPoints { csc232::possiblePoints != 0 ? percentCorrect * csc232::MAX_CORRECTNESS_PTS
                                                           : 0 };
    std::cout << std::left << std::setw( 21 ) << "Correctness Points:"
              << std::right << std::setw( 5 ) << correctnessPoints << std::endl;
    return result;
}
