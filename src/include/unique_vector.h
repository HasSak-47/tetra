#pragma once
#ifndef __UNIQUE_VECTOR_H__
#define __UNIQUE_VECTOR_H__

#include <algorithm>
#include <vector>
#include <memory>

template<class T>
using unique_vector = std::vector< std::unique_ptr<T>>;

template<class T>
inline unique_vector<T> move_unique_vector(unique_vector<T>& source){
    unique_vector<T> destiny;
    size_t size = source.size();
    destiny = unique_vector<T>(size);

    source.clear();
    std::move(source.begin(), source.end(), destiny.begin());

    return destiny;
}

#endif