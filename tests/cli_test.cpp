#include <ltd/ltd.hpp>

using namespace ltd;

auto main(int argc, char** argv) -> int
{
    test_unit tu;

    tu.test([&tu](){
        tu.expect(true, "Expected true");
    });

    tu.test([&tu](){
        tu.expect(true, "Expected true");
    });

    tu.test([&tu](){
        tu.expect(true, "Expected true");
    });
    
    tu.run(argc, argv);
    
    return 0;
}