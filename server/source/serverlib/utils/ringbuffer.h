#pragma once

#include <vector>

template <typename Object>
class RingBuffer
{
public:
    RingBuffer(std::vector<Object> object)
        : m_storage(std::move(object))
        , m_index(0)
    {
    }

    Object& operator()()
    {
        return m_storage[m_index];
    }

    void next()
    {
        m_index = (m_index + 1) % m_storage.size();
    }

private:
    std::vector<Object> m_storage;
    size_t m_index;
};
