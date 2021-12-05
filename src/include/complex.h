#pragma once
#ifndef __COMPLEX_H__
#define __COMPLEX_H__

//this template class need to be declarated so it works in conjuntion wiht complex
template<class T>
class vec2 {
public:
    T x, y;

    vec2() : x(0), y(0) {}
    ~vec2() {};

    vec2(T x) : x(x), y(0) {}
    vec2(T x, T y) : x(x), y(y) {}
    vec2(const vec2<T>& other) : x(other.x), y(other.y) {}
    vec2(vec2<T>&& other) : x(other.x), y(other.y) {}

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
    complex(complex<T>&& other) : vec2<T>(std::move(other)) {}

    complex(const vec2<T>& other) : vec2<T>(other){}
    complex(vec2<T>&& other) : vec2<T>(std::move(other)) {}

    complex<T>& operator=(const complex<T>& other) {
        if(this == &other) return *this;
        (*this).x = other.x;
        (*this).y = other.y;

        return *this;
    }
    complex<T>& operator=(complex<T>&& other) {
        if(this == &other) return *this;
        (*this).x = std::move(other.x);
        (*this).y = std::move(other.y);


        return *this;
    }

    complex<T>& operator+=(const complex<T>& other){
        this->x = other.x + this->x;
        this->y = other.y + this->y;
        return *this;
    }    
    complex<T>& operator-=(const complex<T>& other){
        this->x = other.x - this->x;
        this->y = other.y - this->y;
        return *this;
    }

    complex<T>& operator*=(const complex<T>& other){
        return *this = complex<T>(
            (other.x * this->x) - (other.y * this->y),
            (other.x * this->y) + (other.y * this->x)
        );
    }
    complex<T>& operator/=(const complex<T>& other){
        return *this;
    }

    complex<T> operator+(const complex<T>& other) const {
        return {other.x + this->x, other.y + this->y};
    }
    complex<T> operator*(const complex<T>& other) const;
    complex<T> operator-(const complex<T>& other) const;
    complex<T> operator/(const complex<T>& other) const;
};

typedef vec2<int>   vec2i;
typedef vec2<float> vec2f;

template class vec2<int>;
template class vec2<float>;

typedef complex<int>   complexi;
typedef complex<float> complexf;

template class complex<int>;
template class complex<float>;

#endif