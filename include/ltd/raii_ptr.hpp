#ifndef _LTD_INCLUDE_RAII_PTR_HPP_
#define _LTD_INCLUDE_RAII_PTR_HPP_

#include <functional>

#include "ref_counter.hpp"

namespace ltd
{
    /**
     * @brief
     * Class raii_ptr implements RAII concept.
     * 
     * @details
     * Resource Acquisition Is Initialization or RAII, is a C++ programming 
     * technique which binds the life cycle of a resource that must be acquired 
     * before use (allocated heap memory, thread of execution, open socket, open 
     * file, locked mutex, disk space, database connection—anything that exists 
     * in limited supply) to the lifetime of an object. (cppreference.com)
     * 
     * This class implements the technique and is similar to a smart pointer 
     * framework to track and free object resource. The pointer will track how 
     * many active references point to this class instance and will destruct the 
     * instance once the reference counter reaches 0.
     * 
     * While it is similar to `std::shared_ptr`, it differs in its initial behaviour.
     * When `raii_ptr` is created, it acts like 'std::unique_ptr`. When there
     * is additional pointer references to this instance, it will change its 
     * behaviour to match `std::shared_ptr`. TODO: shared_ptr implemetation.
     */
    template<class T>
    class raii_ptr 
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
         * Construct a new empty raii_ptr
         */
        raii_ptr() : raw_ptr(nullptr), deleter(nullptr)
        {}

        /**
         * @brief
         * Construct a new raii_ptr
         */
        raii_ptr(T *obj, deleter_type dltr) : raw_ptr(obj)
        {
            deleter = dltr;
        }

         /**
         * @brief
         * Construct a new raii_ptr by moving from other raii_ptr.
         * 
         * @details
         * A move contructor to move the content of another `raii_ptr` into this
         * new one and empty the other raii_ptr.
         * 
         * @param other The other raii_ptr
         */
        raii_ptr(raii_ptr&& other)
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
        raii_ptr(const raii_ptr& other) = delete;

        /**
         * @brief
         * Assignment operator is deleted because `raii_ptr` cannot be copied.
         * 
         * @param other
         * @return ptr&
         */
        raii_ptr& operator=(const raii_ptr& other) = delete;

        virtual ~raii_ptr() {
            if (raw_ptr != nullptr) {
                deleter(raw_ptr);
            }
        }
    };

    template<class T>
    raii_ptr<T> wrap_cpp(T* raw)
    {
        raii_ptr<T> ptr(raw,[](T *target) -> void {
            delete target;
        });
        return ptr;
    }

    template<class T>
    raii_ptr<T> wrap_any(T* raw, std::function<void(T*)> dltr)
    {
        raii_ptr<T> ptr(raw, dltr);
        return ptr;
    }
}

#endif // _LTD_INCLUDE_RAII_PTR_HPP_