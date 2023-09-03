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
        std::stringstream buffer { };
        std::streambuf* sbuf;
        /*
         * With the above in place, you can now have tests on output statements 
         * like this:
         * 
         * <some function call or executable that inserts info into output stream...>
         * what you expect to have been inserted
         * const std::string expected{ "1/1/1902\n" };
         * what was actually inserted
         * const std::string actual{ buffer.str( ) };
         * EXPECT_EQ( expected, actual );
         */
    };

    class Task3TestFixture : public CSC232BaseTestFixture
    {
        protected:
        static const int NUM_TEST_GRADES{5};
        static const int NUM_TEST_COURSES{3};
        static constexpr double MAX_TEST_GRADE{95.0};
        double testGrades[NUM_TEST_GRADES] = {75.0, 85.0, 65.0, MAX_TEST_GRADE, 55.0};
        double testGradeBook[NUM_TEST_COURSES][NUM_TEST_GRADES] =
                {
                        {75.0, 85.0, 65.0, 95.0, 55.0},
                        {80.0, 90.0, 70.0, 100.0, 60.0},
                        {70.0, 80.0, 60.0, 90.0, 50.0}
                };
    };

    TEST_F( Task3TestFixture, TaskIsReadyForEvaluation )
    {
        const char* filename   = "csc232.h";
        std::ifstream input_stream{ filename, std::ios::in };
        if (!input_stream)
        {
            FAIL() << "Header file could not be opened.";
        }
        const char* search_string = "TEST_TASK3 TRUE";
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
            cerr << "It appears that you have not toggled TEST_TASK3 to TRUE.\n";
        }
    }
#if TEST_TASK3
    TEST_F( Task3TestFixture, ValidateOneDimensionalArrayProcessing)
    {
        double expected{MAX_TEST_GRADE};
        double actual{maxGrade(NUM_TEST_GRADES, testGrades)};
        EXPECT_DOUBLE_EQ(expected, actual);
    }

    TEST_F( Task3TestFixture, ValidateTwoDimensionalArrayProcessing )
    {
        int expected{1};
        int actual{indexOfMaxGrade(NUM_TEST_COURSES, NUM_TEST_GRADES, testGradeBook)};
        EXPECT_EQ(expected, actual);
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
