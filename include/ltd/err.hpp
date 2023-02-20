#ifndef _LTD_INCLUDE_ERR_HPP_
#define _LTD_INCLUDE_ERR_HPP_

namespace ltd
{
    /**
     * @brief
     * Provides ltd's standard error type and error codes.
     * 
     * @details
     * Class `err` provide simple representation of error and declaration of some
     * standards error for error reporting.
     *      * 
     * Predefined standard errors is vailable to represent an error.
     * ```C++
     *      err::type perform_operation(int value)
     *      {
     *          if (value < 0)
     *              return err::invalid_argument;
     *      }
     * ```
     * 
     * Equality operator can be used to check the kind of the error.
     * ```C++
     *      auto err = perform_operation(0);
     *      if ( err != err::no_error)
     *          return err;
     * ``` 
     * 
     * `err::to_string()` is available to get the null terminated string version.
     */
    class err
    {
    private:
        static constexpr char const *desc[10] =
        {
            "No error",             "Null pointer",             "Index out-of-bound",
            "Invalid argument",     "Type conversion failure",  "Not found",
            "Allocation failure",   "Deallocation failure",     "Invalid operation",
            "Not implemented"
        };

    public:
        enum type
        {
            no_error,               null_pointer,               index_out_of_bound,
            invalid_argument,       type_conversion_failure,    not_found,
            allocation_failure,     deallocation_failure,       invalid_operation,
            not_implemented
        };
        
        err() = delete;

        /**
         * @brief
         * Get the null terminated string version of the error code. 
         */
        static const char* to_string(type err_type);
    };
}

#endif // _LTD_INCLUDE_ERR_HPP_