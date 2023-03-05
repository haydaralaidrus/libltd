#include "../include/ltd/err.hpp"

namespace ltd
{
    const char* err::to_string(type err_type)
    {
        return desc[err_type];
    }

    void err::set_last_error(const std::string& message)
    {
        last_error = message;
    }

    std::string err::get_last_error()
    {
        return last_error;
    }

    std::string err::last_error;

} // namespace ltd
