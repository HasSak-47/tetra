#pragma once
#ifndef __COMPLEX_H__
#define __COMPLEX_H__

//this template class need to be declarated so it works in conjuntion wiht complex
template<class T>
class vec2 {
public:
    T x, y;

    vec2() : x(), y() {}
    ~vec2() {};

    vec2(T x) : x(x), y() {}
    vec2(T x, T y) : x(x), y(y) {}
    vec2(const vec2<T>& other) : x(x), y(y) {}
    vec2(vec2<T>&& other) : x(x), y(y) {}

    vec2& operator=(const vec2<T>& other) {
        if(this == &other) return *this;
        this->x = other.x;
        this->y = other.y;

        return *this;
    }

    vec2& operator=(vec2<T>&& other) {
        if(this == &other) return *this;
        this->x = std::move( other.x );
        this->y = std::move( other.y );

        return *this;
    }

};

template<class T>
class complex : public vec2<T>{
private:
protected:
public:
    complex() : vec2<T>() {}
    ~complex() {}

    complex(T x) : vec2<T>(x){}
    complex(T x, T y) : vec2<T>(x, y){}

    complex(const complex<T>& other) : vec2<T>(other){}
    complex(complex<T>&& other) : vec2<T>(other) {}
    complex& operator=(const complex<T>& other) {
        if(this == &other) return *this;
        (*this) = other;

        return *this;
    }
    complex& operator=(complex<T>&& other) {
        if(this == &other) return *this;
        (*this) = other;

        return *this;
    }

    complex& operator+=(const complex<T>& other){
        this->x = other.x + this->x;
        this->y = other.y + this->y;
        return *this;
    }    
    complex& operator-=(const complex<T>& other){
        this->x = other.x - this->x;
        this->y = other.y - this->y;
        return *this;
    }

    complex& operator*=(const complex<T>& other){
        return *this = complex<T>(
            (other.x * this->x) - (other.y * this->y),
            (other.x * this->y) + (other.y * this->x)
        );
    }
    complex& operator/=(const complex<T>& other){
        return *this;
    }

    complex operator+(const complex<T>& other);
    complex operator*(const complex<T>& other);
    complex operator-(const complex<T>& other);
    complex operator/(const complex<T>& other);
};

typedef vec2<int>   vec2i;
typedef vec2<float> vec2f;

template class vec2<int>;
template class vec2<float>;

typedef vec2<int>   complexi;
typedef vec2<float> complexf;

template class complex<int>;
template class complex<float>;

#endif