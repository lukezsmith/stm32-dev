#include "gtest/gtest.h"

extern "C"
{
#include "simple_module.h"
}

namespace my
{
  namespace project
  {
    namespace
    {

      // The fixture for testing class Foo.
      class SimpleModuleTest : public ::testing::Test
      {
      protected:
        // You can remove any or all of the following functions if their bodies would
        // be empty.

        SimpleModuleTest()
        {
          // You can do set-up work for each test here.
        }

        ~SimpleModuleTest() override
        {
          // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        void SetUp() override
        {
          // Code here will be called immediately after the constructor (right
          // before each test).
        }

        void TearDown() override
        {
          // Code here will be called immediately after each test (right
          // before the destructor).
        }

        // Class members declared here can be used by all tests in the test suite
        // for Foo.
      };

      // Tests that the Foo::Bar() method does Abc.
      TEST_F(SimpleModuleTest, MethodBarDoesAbc)
      {
        const std::string input_filepath = "this/package/testdata/myinputfile.dat";
        const std::string output_filepath = "this/package/testdata/myoutputfile.dat";
        // EXPECT_EQ(f.Bar(input_filepath, output_filepath), 0);
        EXPECT_EQ(input_filepath, output_filepath);
      }

      // Tests that Foo does Xyz.
      TEST_F(SimpleModuleTest, DoesXyz)
      {
        // Exercises the Xyz feature of Foo.
      }

    } // namespace
  }   // namespace project
} // namespace my

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}