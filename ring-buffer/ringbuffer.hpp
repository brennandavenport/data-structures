#include <cstddef>
#include <memory>
#include <stdexcept>

namespace bd {

// apis
template <typename T, std::size_t N>
class ringbuffer {
private:
    std::size_t m_head{};
    std::size_t m_tail{};
    std::unique_ptr<T[]> m_data{};
    bool m_full{ false };
    bool m_empty{ true };

public:
    explicit ringbuffer();
    ringbuffer(const ringbuffer& other) = delete;
    ringbuffer& operator=(const ringbuffer& other) = delete;
    ringbuffer(ringbuffer&& other) = delete;
    ringbuffer&& operator=(ringbuffer&& other) = delete;

    [[nodiscard]] bool push(const T& val);
    T peek() const;
    T pop();

    std::size_t size() const { return (m_head - m_tail + N) % N; }
    std::size_t capacity() const { return N; }
    bool isFull() const { return m_full; }
    bool isEmpty() const { return m_empty; }
    void clear();
};

} // namespace bd

// implementation
//
// constructors
template <typename T, std::size_t N>
bd::ringbuffer<T, N>::ringbuffer() {
    m_data = std::make_unique<T[]>(N);
}

// apis
template <typename T, std::size_t N>
bool bd::ringbuffer<T, N>::push(const T& val) {
    m_empty = false;
    if (m_full) {
        return false;
    }

    m_data[m_head] = val;
    m_head = (m_head + 1) % N;

    if (m_head == m_tail) {
        m_full = true;
    }

    return true;
}

template <typename T, std::size_t N>
T bd::ringbuffer<T, N>::peek() const {
    if (m_empty) {
        throw std::out_of_range("Ring Buffer is empty! Nothing to see");
    }
    return m_data[m_tail];
}

template <typename T, std::size_t N>
T bd::ringbuffer<T, N>::pop() {
    if (m_empty) {
        throw std::out_of_range("Ring Buffer is empty! Nothing to pop");
    }
    T val = m_data[m_tail];
    m_tail = (m_tail + 1) % N;

    if (m_tail == m_head) {
        m_empty = true;
    }

    return val;
}

template <typename T, std::size_t N>
void bd::ringbuffer<T, N>::clear() {
    m_data.reset(nullptr);
    m_data = std::make_unique<T[]>(N);
    m_empty = true;
    m_full = false;
    m_head = 0uz;
    m_tail = 0uz;
}
