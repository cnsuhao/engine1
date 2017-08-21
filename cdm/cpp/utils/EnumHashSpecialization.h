/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

#pragma once

#include <functional>

template<typename E>
class enum_hash
{
public:
    size_t operator()(const E& e) const
    {
        using UnderlyingType = typename std::underlying_type<E>::type;

        return std::hash<UnderlyingType>()(static_cast<UnderlyingType>(e));
    }
};
