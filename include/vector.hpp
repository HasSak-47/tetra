#ifndef __VECTOR_H__
#define __VECTOR_H__

template<typename T>
struct Vector4{
    union{
        struct {T r, g, b, a;};
        struct {T x, y, z, w;};
        struct {T n, i, j, k;};
        struct {T m[4]; };
    };
};


template<typename T>
struct Vector3{
    union{
        struct {T r, g, b; };
        struct {T x, y, z; };
        struct {T n, i, j; };
        struct {T m[3]; };
    };
};

template<typename T>
struct Vector2{
    union{
        struct {T r, g;};
        struct {T x, y;};
        struct {T n, i;};
        struct {T m[2]; };
    };
};
#endif
