#ifndef _LTD_INCLUDE_REF_COUNTERS_HPP_
#define _LTD_INCLUDE_REF_COUNTERS_HPP_

#include <atomic>

#include "std_alias.hpp"
#include "err.hpp"

namespace ltd
{
    /**
     * @brief
     * Reference counter for atomic reference counting.
     *
     * Reference counters provide reference counting mechanish that can be used
     * for automatic object deconstruction and memory deallocation.
     *
     * This reference counter provides atomic counter, which means it is thread
     * safe and lock free.
     */
    class ref_counter
    {
        /**
         * @brief
         * Construct a new ref counter object
         *
         * The only constructor for ref_counter.
         *
         * @param data The state to store in the `ref_counter`.
         */
        ref_counter();

        // Remove ctors and assignment operator
        ref_counter(const ref_counter& other) = delete;
        ref_counter& operator=(const ref_counter& other) = delete;

    private:
        std::atomic_size_t counter;

    public:
        /**
         * @brief
         * Increment the reference.
         */
        void inc();

        /**
         * @brief
         * Decrement the reference counter.
         *
         * @return true If the counter reached 0.
         * @return false If the counter is more than 0.
         */
        bool dec();

    };
}

#endif // _LTD_INCLUDE_REF_COUNTERS_HPP_
