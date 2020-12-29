#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <optional>
#include <functional>
#include <utility>
#include <cstdint>
#include <string>
#include <fstream>
#include <unordered_map>
#include <map>
#include <stdexcept>



/********************************************************
*                      Type Aliases                     *
********************************************************/

template<typename T>
using LzShrPtr = ::std::shared_ptr<T>;

template<typename T>
using LzUniPtr = ::std::unique_ptr<T>;

template<typename T>
using LzShrPtrVec = ::std::vector<::std::shared_ptr<T>>;

template<typename T>
using LzShrPtrList = ::std::list<::std::shared_ptr<T>>;

template<typename T>
using LzVec = ::std::vector<T>;

template<typename T>
using LzList = ::std::list<T>;

template<typename Key, typename Value>
using LzUnMap = ::std::unordered_map<Key, Value>;

template<typename Key, typename Value>
using LzMap = ::std::map<Key, Value>;

template<typename RType, typename ... Args>
using LzFunc = ::std::function<RType(Args...)>;

template<typename First, typename Second>
using LzPair = ::std::pair<First, Second>;

using LzString = ::std::string;

using LzSizeT = ::std::size_t;



/********************************************************
*                     Common macros                     *
********************************************************/

#define LZ_ENGINE_GUARD_FATAL(statement, message)\
    if (!statement) {\
        throw std::runtime_error{ message };\
    }