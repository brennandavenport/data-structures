#include <cstddef>
#include <memory>
#include <type_traits>

namespace my {

template <typename T, typename Deleter = std::default_delete<T>>
    requires(!std::is_reference_v<T>)
class unique_ptr {
public:
    // this should fall back to T* but idk how
    using pointer = std::remove_reference<Deleter>::type::pointer;
    using element_type = T;
    using deleter_type = Deleter;

    // copy ctor
    unique_ptr(const unique_ptr& other) = delete;

    // constructors
    // destructor
    //

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
    pointer release() noexcept;

    // replace the managed object
    void reset(pointer ptr = pointer()) noexcept;

    // swaps content of this and other
    void swap(unique_ptr& other) noexcept;

    pointer get() const noexcept;

    Deleter& get_deleter() noexcept;
    const Deleter& get_deleter() const noexcept;

    explicit operator bool() const noexcept;

    // add operator*

    pointer operator->() const noexcept;
};

} // namespace my
