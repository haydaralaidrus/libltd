#ifndef _LTD_INCLUDE_AUTO_DLTR_HPP_
#define _LTD_INCLUDE_AUTO_DLTR_HPP_

#include <functional>

#include "ref_counter.hpp"

namespace ltd
{
    /**
     * @brief
     * Class auto_dltr implements automatic resource destruction and deallocation.
     * 
     * @details
     * This class implements a smart pointer framework to track and free object
     * resource. The pointer will track how many active references point to this
     * class instance and will destruct the instance once the reference counter
     * reaches 0.
     * 
     * While it is similar to `std::shared_ptr`, it differs in its initial behaviour.
     * When `auto_dltr` is created, it acts like 'std::unique_ptr`. When there
     * is additional pointer references to this instance, it will change its 
     * behaviour to match `std::shared_ptr`.
     */
    template<class T>
    class auto_dltr 
    {
    public: // types
        using element_type = T;
        using deleter_type = std::function<void(T*)>;

    private:
        element_type *raw_ptr;
        deleter_type deleter;

    public:
        /**
         * @brief
         * Construct a new empty auto_dltr
         */
        auto_dltr() : raw_ptr(nullptr),deleter(nullptr)
        {}

        /**
         * @brief
         * Construct a new auto_dltr
         */
        auto_dltr(T *obj, deleter_type dltr) : raw_ptr(obj)
        {
            deleter = dltr;
        }

         /**
         * @brief
         * Construct a new auto_dltr by moving from other auto_dltr.
         * 
         * @details
         * A move contructor to move the content of another `auto_dltr` into this
         * new one and empty the other auto_dltr.
         * 
         * @param other The other auto_dltr
         */
        auto_dltr(auto_dltr&& other)
        {
            raw_ptr       = other.raw_ptr;
            other.raw_ptr = nullptr;

            deleter         = other.deleter;
            other.deleter   = nullptr;
        }

        /**
         * @brief
         * Copy constructors are deleted because this class is not copy-able.
         * 
         * @param other
         */
        auto_dltr(const auto_dltr& other) = delete;

        /**
         * @brief
         * Assignment operator is deleted because `auto_dltr` cannot be copied.
         * 
         * @param other
         * @return ptr&
         */
        auto_dltr& operator=(const auto_dltr& other) = delete;

        virtual ~auto_dltr() {
            if (raw_ptr != nullptr) {
                deleter(raw_ptr);
            }
        }
    };

    template<class T>
    auto_dltr<T> wrap_cpp(T* raw)
    {
        auto_dltr<T> ptr(raw,[](T *target) -> void {
            delete target;
        });
        return ptr;
    }
}

#endif // _LTD_INCLUDE_AUTO_DLTR_HPP_