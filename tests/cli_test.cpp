#include <ltd/ltd.hpp>

using namespace ltd;

auto main(int argc, char** argv) -> int
{
    test_unit tu;

    tu.test([&tu](){
        tu.expect(0, 0);
    });

    tu.test([&tu](){
        tu.expect(0.1, 0.1);
    });

    tu.test([&tu](){
        tu.expect("true", "true");
    });
    
    tu.run(argc, argv);
    
    return 0;
}