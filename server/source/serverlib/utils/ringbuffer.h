#pragma once

#include <vector>
#include <set>

template <typename Object>
class RingBuffer
{
public:
    RingBuffer(std::vector<Object> object)
        : m_storage(std::move(object))
        , m_removed()
        , m_index(0)
    {
    }

    Object& operator()()
    {
        return m_storage[m_index];
    }

    void next()
    {
        do {
            m_index = (m_index + 1) % m_storage.size();
        } while (m_removed.count(m_index)); // Skip removed
    }

    size_t size()
    {
        return m_storage.size() - m_removed.size();
    }

    std::vector<Object>& storage()
    {
        return m_storage;
    }

    void remove(const Object& entry)
    {
        const auto it = std::find(m_storage.cbegin(), m_storage.cend(), entry);

        if (it == m_storage.cend())
            return;

        const size_t pos = it - m_storage.cbegin();

        m_removed.insert(pos);
    }

private:
    std::vector<Object> m_storage;
    std::set<size_t> m_removed;
    size_t m_index;
};
