/// @file unique_ptr.hpp
/// @brief An implementation of unique_ptr

#include <cstddef>
#include <memory>
#include <type_traits>

namespace my {

/// @brief Owns and manages an object through a pointer
///
/// Deletes the managed pointer when it goes out of scoped (RAII)
///
/// @tparam T type of managed object, requires not a reference
/// @tparam Deleter type, defaults to std::default_delete, requires default constructible
template <typename T, typename Deleter = std::default_delete<T>>
    requires(!std::is_reference_v<T> && std::is_default_constructible_v<Deleter>)
class unique_ptr {
public:
    // this should fall back to T* but idk how
    using pointer = std::remove_reference<Deleter>::type::pointer;
    using element_type = T;
    using deleter_type = Deleter;

    // copy ctor
    unique_ptr(const unique_ptr& other) = delete;

    // constructors
    unique_ptr() noexcept
        : m_ptr(nullptr)
        , m_deleter() {}
    unique_ptr(std::nullptr_t) noexcept
        : m_ptr(nullptr)
        , m_deleter() {}

    explicit unique_ptr(pointer p) noexcept
        : m_ptr(p)
        , m_deleter() {}

    // 5 move constructor
    unique_ptr(unique_ptr&& other) noexcept
        : m_ptr(other.release())
        , m_deleter(other.get_deleter()) {}

    // destructor
    ~unique_ptr() {
        if (get() != nullptr) {
            get_deleter()(get());
        }
    }

    // assignment operators
    // move 1
    unique_ptr& operator=(unique_ptr&& other) noexcept;
    // move 2 templated
    template <typename U, typename E>
    unique_ptr& operator=(unique_ptr<U, E>&& other) noexcept;
    // null ptr
    unique_ptr& operator=(std::nullptr_t) noexcept;
    // copy 4
    void operator=(const unique_ptr& other) = delete;

    // releases the ownership of the managed object
    [[nodiscard("Returns a pointer")]] pointer release() noexcept {
        pointer temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    // replace the managed object
    void reset(pointer ptr = pointer()) noexcept {
        // delete pointer
        if (get() != nullptr) {
            get_deleter()(get());
        }

        // write replacement
        m_ptr = ptr;
    }

    // swaps content of this and other
    void swap(unique_ptr& other) noexcept;

    pointer get() const noexcept { return m_ptr; }

    Deleter& get_deleter() noexcept { return m_deleter; }
    const Deleter& get_deleter() const noexcept { return m_deleter; }

    explicit operator bool() const noexcept { return get() != nullptr; }

    // add operator*

    pointer operator->() const noexcept;

private:
    pointer m_ptr;
    deleter_type m_deleter;
};

} // namespace my
