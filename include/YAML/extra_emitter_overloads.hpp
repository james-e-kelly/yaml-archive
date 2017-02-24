#pragma once

#include <array>
#include <bitset>
#include <boost/array.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <yaml-cpp/emitter.h>

namespace YAML {
namespace detail {

template <class SequenceLike>
Emitter& EmitSeq(Emitter& emit, const SequenceLike& sequence)
{
    emit << BeginSeq;
    for (const auto& item : sequence) emit << item;
    emit << EndSeq;
    return emit;
}

template <class MapLike> Emitter& EmitMap(Emitter& emit, const MapLike& map)
{
    emit << BeginMap;
    for (const auto& kv : map) emit << Key << kv.first << Value << kv.second;
    emit << EndMap;
    return emit;
}

template <std::size_t Index = 0, typename... Args>
typename std::enable_if<Index == sizeof...(Args), Emitter&>::type
EmitTuple(Emitter& emit, const std::tuple<Args...>& /*tup*/)
{
    return emit;
}

template <std::size_t Index = 0, typename... Args>
typename std::enable_if<Index != sizeof...(Args), Emitter&>::type
EmitTuple(Emitter& emit, const std::tuple<Args...>& tup)
{
    emit << std::get<Index>(tup);
    return EmitTuple<Index + 1, Args...>(emit, tup);
}

} // namespace detail

// native array
template <class T, std::size_t N>
Emitter& operator<<(Emitter& emit, const T (&t)[N])
{
    return detail::EmitSeq(emit, t);
}

// std::vector
template <class T, class Alloc>
Emitter& operator<<(Emitter& emit, const std::vector<T, Alloc>& t)
{
    return detail::EmitSeq(emit, t);
}

// std::list
template <class T, class Alloc>
Emitter& operator<<(Emitter& emit, const std::list<T, Alloc>& t)
{
    return detail::EmitSeq(emit, t);
}

// std::deque
template <class T, class Alloc>
Emitter& operator<<(Emitter& emit, const std::deque<T, Alloc>& t)
{
    return detail::EmitSeq(emit, t);
}

// std::forward_list
template <class T, class Alloc>
Emitter& operator<<(Emitter& emit, const std::forward_list<T, Alloc>& t)
{
    return detail::EmitSeq(emit, t);
}

// std::array
template <class T, std::size_t N>
Emitter& operator<<(Emitter& emit, const std::array<T, N>& t)
{
    return detail::EmitSeq(emit, t);
}

// boost::array
template <class T, std::size_t N>
Emitter& operator<<(Emitter& emit, const boost::array<T, N>& t)
{
    return detail::EmitSeq(emit, t);
}

// std::map
template <class Key, class T, class Compare, class Alloc>
Emitter& operator<<(Emitter& emit, const std::map<Key, T, Compare, Alloc>& t)
{
    return detail::EmitMap(emit, t);
}

// std::unordered_map
template <class Key, class T, class Hash, class KeyEqual, class Alloc>
Emitter& operator<<(Emitter& emit,
                    const std::unordered_map<Key, T, Hash, KeyEqual, Alloc>& t)
{
    return detail::EmitMap(emit, t);
}

// boost::unordered_map
template <class Key, class T, class Hash, class KeyEqual, class Alloc>
Emitter&
operator<<(Emitter& emit,
           const boost::unordered_map<Key, T, Hash, KeyEqual, Alloc>& t)
{
    return detail::EmitMap(emit, t);
}

// std::set
template <class Key, class Compare, class Alloc>
Emitter& operator<<(Emitter& emit, const std::set<Key, Compare, Alloc>& t)
{
    return detail::EmitSeq(emit, t);
}

// std::unordered_set
template <class Key, class Hash, class KeyEqual, class Alloc>
Emitter& operator<<(Emitter& emit,
                    const std::unordered_set<Key, Hash, KeyEqual, Alloc>& t)
{
    return detail::EmitSeq(emit, t);
}

// boost::unordered_set
template <class Key, class Hash, class KeyEqual, class Alloc>
Emitter& operator<<(Emitter& emit,
                    const boost::unordered_set<Key, Hash, KeyEqual, Alloc>& t)
{
    return detail::EmitSeq(emit, t);
}

// std::bitset
template <std::size_t N>
Emitter& operator<<(Emitter& emit, const std::bitset<N>& bits)
{
    return emit << bits.to_string();
}

// std::pair
template <class First, class Second>
Emitter& operator<<(Emitter& emit, const std::pair<First, Second>& pair)
{
    emit << BeginSeq << pair.first << pair.second << EndSeq;
    return emit;
}

// std::tuple
template <typename... Args>
Emitter& operator<<(Emitter& emit, const std::tuple<Args...>& tup)
{
    emit << BeginSeq;
    detail::EmitTuple(emit, tup);
    emit << EndSeq;
    return emit;
}

// std::tuple -- empty
inline Emitter& operator<<(Emitter& emit, const std::tuple<>& /*tup*/)
{
    emit << Null;
    return emit;
}

} // namespace YAML