#pragma once

#include <cstddef>
#include <initializer_list>
#include <new>
#include <utility>

namespace bd {

template <typename T>
class vector {
public:
    vector() = default;

    explicit vector(std::size_t size)
        : m_size{ size }
        , m_capacity{ size } {
        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));

        for (std::size_t i{}; i < m_size; ++i) {
            ::new (m_data + i) T();
        }
    }

    explicit vector(std::size_t size, const T& value)
        : m_size{ size }
        , m_capacity{ size } {

        m_data = static_cast<T*>(::operator new(m_capacity * sizeof(T)));

        for (std::size_t i; i < m_size; ++i) {
            ::new (m_data + i) T{ value };
        }
    }

    vector(std::initializer_list<T>);

    // rule of five
    // copy
    // vector(const my::vector<T>& other);
    // my::vector<T>& operator=(const my::vector<T>& other);
    //
    // // move
    // vector(my::vector<T>&& other);
    // my::vector<T>& operator=(my::vector<T>&& other);

    ~vector() {
        clear();
        ::operator delete(m_data);
    }

    // element access
    const T& operator[](std::size_t idx) const { return m_data[idx]; }
    T& operator[](std::size_t idx) { return m_data[idx]; }

    const T& front() const { return m_data[0]; }
    T& front() { return m_data[0]; }

    const T& back() const { return m_data[m_size - 1]; }
    T& back() { return m_data[m_size - 1]; }

    const T* data() const { return m_data; }
    T* data() { return m_data; }

    // capacity
    [[nodiscard]] bool empty() const { return m_size == 0; }

    [[nodiscard]] std::size_t size() const { return m_size; }

    [[nodiscard]] std::size_t max_size() const;

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= m_capacity)
            return;

        realloc(new_capacity);
    }

    [[nodiscard]] std::size_t capacity() const { return m_capacity; }

    void shrink_to_fit() { realloc(m_size); }
    // end of capacity

    // modifiers
    void clear() {
        if (m_size == 0)
            return;

        for (std::size_t i{}; i < m_size; ++i) {
            m_data[i].~T();
        }

        m_size = 0;
    }

    // research iterators
    // void insert(std::iterator, const T& value);
    // void emplace();
    // void erase();
    void push_back(const T& value) {
        if (m_size == m_capacity) {
            std::size_t new_capacity =
                (m_capacity == 0) ? BASE_CAPACITY : m_capacity * CAPACITY_MULT;
            realloc(new_capacity);
        }
        // placement new
        ::new (m_data + m_size) T(value);
        ++m_size;
    }

    void pop_back() {
        if (m_size == 0)
            return;

        --m_size;
        m_data[m_size].~T();
    }

    void resize(std::size_t new_size) {
        if (m_size == new_size)
            return;

        if (m_size > new_size) {
            for (std::size_t i{ m_size }; i > new_size; --i) {
                pop_back();
            }
        } else {
            for (std::size_t i{ m_size }; i < new_size; ++i) {
                push_back(T());
            }
        }
    }

private:
    void realloc(std::size_t new_capacity) {
        T* old_data = m_data;
        m_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        for (std::size_t i{}; i < m_size; ++i) {
            // unitilized bytes
            // m_data[i] = std::move(old_data[i]);
            // cast back to void* call move constructor on type T
            // if move fails default to copy
            ::new (m_data + i) T(std::move(old_data[i]));
            old_data[i].~T();
        }
        m_capacity = new_capacity;
        ::operator delete(old_data);
    }

private:
    T* m_data{ nullptr };
    std::size_t m_size{ 0 };
    std::size_t m_capacity{ 0 };
    static constexpr std::size_t BASE_CAPACITY{ 2 };
    static constexpr std::size_t CAPACITY_MULT{ 2 };
};

}; // namespace bd
