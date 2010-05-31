#ifndef SLC_MATH_VECTOR_H
#define SLC_MATH_VECTOR_H

#include <cmath>

namespace math
{
    template<typename T>
    class Vector
    {
        public:

        Vector();
        Vector(T _x, T _y);
        ~Vector();


        void operator=(const Vector<T> &a);

        // assignments
        void operator=(const Vector<T> &a);
        void operator+=(const Vector<T> &a);
        void operator-=(const Vector<T> &a);
        void operator*=(T a);
        void operator/=(T a);

        void norm();
        void setLength(T l);
        T mag();

        T x();
        T y();
        void set(T, T);



        private:
        T tx;
        T ty;
    };
    // addition, subtraction and negation

    template<typename T> Vector<T> operator+(const Vector<T> &a, const Vector<T> &b);
    template<typename T> Vector<T> operator-(const Vector<T> &a, const Vector<T> &b);
    template<typename T> Vector<T> operator-(const Vector<T> &a);
    // multiplication
    template<typename T> Vector<T> operator*(const Vector<T> &a, T f);
    template<typename T> Vector<T> operator*(T f, const Vector<T> &a);
    // division
    template<typename T> Vector<T> operator/(const Vector<T> &a, T f);
    template<typename T> Vector<T> operator/(T f, const Vector<T> &a);
    // dot
    template<typename T> T operator*(const Vector<T> &a, const Vector<T> &b);

}
#endif
