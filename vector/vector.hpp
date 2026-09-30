#pragma once

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>

namespace bd {

template <typename T>
class vector {
public:
    vector() = default;

    explicit vector(std::size_t size)
        : m_size{ size }
        , m_capacity{ size } {
        m_data = std::make_unique<T[]>(m_capacity);
    }

    explicit vector(std::size_t size, const T& value)
        : m_size{ size }
        , m_capacity{ size } {

        m_data = std::make_unique<T[]>(m_capacity);

        for (std::size_t i{ 0uz }; i < m_size; ++i) {
            m_data[i] = T(value);
        }
    }

    vector(std::initializer_list<T> list)
        : m_size{ list.size() }
        , m_capacity{ list.size() } {

        m_data = std::make_unique<T[]>(m_capacity);

        std::size_t i{ 0uz };
        for (auto it = list.begin(); it != list.end(); it++) {
            m_data[i] = std::move(*it);
            i++;
        }
    }

    // rule of five
    // copy
    // vector(const my::vector<T>& other);
    // my::vector<T>& operator=(const my::vector<T>& other);
    //
    // // move
    // vector(my::vector<T>&& other);
    // my::vector<T>& operator=(my::vector<T>&& other);

    ~vector() {}

    // element access
    const T& operator[](std::size_t idx) const { return m_data[idx]; }
    T& operator[](std::size_t idx) { return m_data[idx]; }

    const T& front() const { return m_data[0]; }
    T& front() { return m_data[0]; }

    const T& back() const { return m_data[m_size - 1]; }
    T& back() { return m_data[m_size - 1]; }

    const T* data() const { return m_data.get(); }
    T* data() { return m_data.get(); }

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

        m_data = std::make_unique<T[]>(m_capacity);
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
        m_data[m_size] = T(value);
        ++m_size;
    }

    void pop_back() {
        if (m_size == 0)
            return;

        --m_size;
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
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);

        for (std::size_t i{}; i < m_size; ++i) {
            new_data[i] = std::move(m_data[i]);
        }
        m_capacity = new_capacity;
        m_data = std::move(new_data);
    }

private:
    std::unique_ptr<T[]> m_data{ nullptr };
    std::size_t m_size{ 0 };
    std::size_t m_capacity{ 0 };
    static constexpr std::size_t BASE_CAPACITY{ 2 };
    static constexpr std::size_t CAPACITY_MULT{ 2 };
};

template <typename T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs) {
    if (lhs.size() == rhs.size()) {
        for (std::size_t i{ 0uz }; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs) {
    if (lhs.size() == rhs.size()) {
        for (std::size_t i{ 0uz }; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i]) {
                return true;
            }
        }
        return false;
    }
    return true;
}

template <typename T>
bool operator<(const vector<T>& lhs, const vector<T>& rhs) {
    if (lhs.size() == rhs.size()) {
        for (std::size_t i{ 0uz }; i < lhs.size(); i++) {
            if (lhs[i] < rhs[i]) {
                return true;
            }
        }
        return false;

    } else {
        return lhs.size() < rhs.size();
    }
}

template <typename T>
bool operator<=(const vector<T>& lhs, const vector<T>& rhs) {
    return lhs == rhs || lhs < rhs;
}

template <typename T>
bool operator>(const vector<T>& lhs, const vector<T>& rhs) {
    // if lhs is not less than rhs then it must be lhs >= rhs
    return !(lhs < rhs) && lhs != rhs;
}

template <typename T>
bool operator>=(const vector<T>& lhs, const vector<T>& rhs) {
    return !(lhs < rhs);
}

}; // namespace bd
