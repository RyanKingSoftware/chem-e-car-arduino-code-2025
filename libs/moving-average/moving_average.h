#ifndef _MOVING_AVERAGE_H_
#define _MOVING_AVERAGE_H_

template<typename T, size_t Size>
class MovingAverage
{
public:
    MovingAverage() noexcept
        : m_idx(0), m_count(0), m_total(0), m_average(0)
    {
        for (size_t i = 0; i < Size; i++)
        {
            m_list[i] = T{};
        }
    }

    double getAverage() const noexcept
    {
        return m_average;
    }

    void insert(const T& data) noexcept
    {
        // Subtract the old value being overwritten (only after Size elements have been added)
        if (m_count >= Size)
        {
            m_total -= m_list[m_idx];
        }
        else
        {
            m_count++; // Increase count until it reaches Size
        }

        // Insert new value
        m_list[m_idx] = data;
        m_total += data;

        // Move index forward, resetting to 0 when reaching Size
        m_idx++;
        if (m_idx == Size) m_idx = 0;

        // Compute new average (exclude initial zeros if not full yet)
        m_average = static_cast<double>(m_total) / m_count;
    }

private:
    T m_list[Size];
    size_t m_idx;
    size_t m_count; // Number of elements inserted, capped at Size
    T m_total;
    double m_average;
};

#endif // _MOVING_AVERAGE_H_