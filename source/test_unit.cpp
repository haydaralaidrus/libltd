#include "../include/ltd/test_unit.hpp"
#include "../include/ltd/fmt.hpp"
#include "../include/ltd/cli_flags.hpp"

using namespace ltd;

namespace ltd
{

    test_unit::test_unit() : failed(false)
    {}

    test_unit::~test_unit()
    {}

    void test_unit::test(std::function<void()> test_function)
    {
        test_cases.push_back(test_function);
    }

    void test_unit::run(int argc, char** argv)
    {
        verbosity = 0;

        int all       = 0;
        int help      = 0;
        int test_id   = -1;
        int test_count= -1;

        cli_flags flags;

        flags.bind(&all, 'a', "all", "Run all tests.");
        flags.bind(&help, 'h', "help", "Displays this help.");
        flags.bind(&verbosity, 'v', "verbose", "Verbose logging.");
        flags.bind(&test_id, 'i', "test-id", "Specifies test-id to run.");
        flags.bind(&test_count, 'c', "count", "Print the number of tests available.");
        flags.parse(argc, argv);

        if (argc == 1) {
            fmt::println("Usage: %s -havci [test-id]", argv[0]);
            flags.print_help(4);
        } else if (help > 0) {
            fmt::println("Usage: %s -havci [test-id]", argv[0]);
            flags.print_help(4);
        } else if (test_count > 0) {
            fmt::println("%d", test_cases.size());
        } else if (all > 0) {
            int case_no = 0;

            for(auto test_case : test_cases) {
                test_case();
                case_no++;
                if (failed) {
                    fmt::println("Case no %d failed", case_no);
                    break;
                }
            }

            if (failed == false) {
                fmt::println("-ok-");
            }

        } else if (test_id >= 0) {
            if (test_id >= 0 && test_id < test_cases.size()) {
                test_cases[test_id]();
                if (failed == false)
                    fmt::println("-ok-");
            } else {
                fmt::println("Invalid test id.");
                fmt::println("Specify the test id you want to run or use no argument to get the number of test case.");
            }
        } else {
            fmt::println("Invalid use of program arguments.");
            fmt::println("Specify the test id you want to run or use no argument to get the number of test case.");
            fmt::println("Usage: %s -havci [test-id]", argv[0]);
            flags.print_help(4);       
        }

    }

    void test_unit::expect(const std::string& test_value, const std::string& expected_value)
    {
        if (verbosity > 0)
            fmt::println("Expected: %s, Value: %s", expected_value, test_value);

        if (test_value != expected_value) {
            if (verbosity == 0)
                fmt::println("Expected: %s, Value: %s", expected_value, test_value);
            failed = true;
        }
    }

    void test_unit::expect(int test_value, int expected_value)
    {
        if (verbosity > 0)
            fmt::println("Expected: %d, Value: %d", expected_value, test_value);

        if (test_value != expected_value) {
            if (verbosity == 0)
                fmt::println("Expected: %d, Value: %d", expected_value, test_value);
            failed = true;
        }
    }

    void test_unit::expect(double test_value, double expected_value)
    {
        if (verbosity > 0)
            fmt::println("Expected: %f, Value: %f", expected_value, test_value);

        if (test_value != expected_value) {
            if (verbosity == 0)
                fmt::println("Expected: %f, Value: %f", expected_value, test_value);
            failed = true;
        }
    }

} // namespace ltd