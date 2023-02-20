#include "../include/ltd/err.hpp"

namespace ltd
{
    const char* err::to_string(type err_type)
    {
        return desc[err_type];
    }

} // namespace ltd
