#pragma once

#include "cx_algorithm.h"
#include "cx_pair.h"

#include <array>
#include <cstddef>
#include <stdexcept>

namespace cx
{
  template <typename Key, typename Value, std::size_t Size = 5>
  class map
  {
  public:
    constexpr auto begin() const { return m_data.begin(); }
    constexpr auto begin() { return m_data.begin(); }

    constexpr auto end() const { return m_data.begin() + m_size; }
    constexpr auto end() { return m_data.begin() + m_size; }

    constexpr auto cbegin() const { return m_data.begin(); }
    constexpr auto cend() const { m_data.begin() + m_size; }

    constexpr auto find(const Key &k)
    {
      return find_impl(*this, k);
    }

    constexpr auto find(const Key &k) const
    {
      return find_impl(*this, k);
    }

    constexpr const Value &at(const Key &k) const
    {
      const auto itr = find(k);
      if (itr != end()) { return itr->second; }
      else { throw std::range_error("Key not found"); }
    }

    constexpr Value &operator[](const Key &k) {
      const auto itr = find(k);
      if (itr == end()) {
        auto &data = m_data[m_size++];
        data.first = k;
        return data.second;
      } else {
        return itr->second;
      }
    }

  private:
    template<typename This>
    static constexpr auto find_impl(This &&t, const Key &k)
    {
      return cx::find_if(t.begin(), t.end(),
                         [&k] (const auto &d) { return d.first == k; });
    }

    std::array<cx::pair<Key, Value>, Size> m_data{};
    std::size_t m_size{0};
  };
}