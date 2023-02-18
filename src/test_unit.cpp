#include "../inc/test_unit.hpp"
#include "../inc/fmt.hpp"

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
        if (argc == 1) {
            fmt::println("%d", test_cases.size());
        } else if (argc == 2) {
            std::string value = argv[1];
            bool isnumber = std::all_of(value.begin(), value.end(), ::isdigit);

            if (isnumber) {
                int index = std::stol(value);

                if (index >= 0 && index < test_cases.size()) {
                    test_cases[index]();
                    if (failed == false)
                        fmt::println("-ok-");
                } else {
                    fmt::println("Invalid test id.");
                    fmt::println("Specify the test id you want to run or use no argument to get the number of test case.");
                }
            } else {
                fmt::println("Invalid use of program arguments.");
                fmt::println("Specify the test id you want to run or use no argument to get the number of test case.");
            }
        }
    }

    void test_unit::expect(bool condition, const std::string& message)
    {
        if (condition == false) {
            fmt::println("%s", message);
            failed = true;
        }
    }

    void test_unit::expect(const std::string& test_value, const std::string& expected_value)
    {
        if (test_value != expected_value) {
            fmt::println("Expected: %s, Value: %s", expected_value, test_value);
            failed = true;
        }
    }

} // namespace ltd