#include <ltd/ltd.hpp>
#include <vector>

using namespace ltd;

int test_counter = 0;

class test
{
    int data;

public:
    test() : data(0) {
        test_counter++;
    }

    int get_data() const { return data; }
    void set_data(int d) { data = d; }

    virtual ~test() {
        test_counter--;
    }
};

auto main(int argc, char** argv) -> int
{
    test_unit tu;

    tu.test([&tu](){
        {
            test *t = new test();
            raii_ptr<test> tt = wrap_cpp<test>(t);
            
            tu.expect(test_counter, 1);
        }

        tu.expect(test_counter, 0);
    });

    tu.test([&tu](){
        {
            std::vector<raii_ptr<test>> tests;

            for (int i=0; i<10; i++) {
                test *t = new test();
                raii_ptr<test> tt = wrap_cpp<test>(t);
                tests.push_back(std::move(tt));
            }
            
            tu.expect(test_counter, 10);
        }

        tu.expect(test_counter, 0);
    });

    tu.test([&tu](){
        {
            std::vector<raii_ptr<test>> tests;

            for (int i=0; i<1000; i++) {
                test *t = new test();
                raii_ptr<test> tt = wrap_cpp<test>(t);
                tests.push_back(std::move(tt));
            }
            
            tu.expect(test_counter, 1000);
        }

        tu.expect(test_counter, 0);
    });

    tu.run(argc, argv);

    return 0;
}