#pragma once
#ifndef __UNIQUE_VECTOR_H__
#define __UNIQUE_VECTOR_H__

#include <vector>
#include <memory>

template<class T>
using unique_vector = std::vector< std::unique_ptr<T>>;

#endif