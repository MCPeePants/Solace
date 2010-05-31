#include "math/vector.h"

namespace math
{
    template<typename T> Vector<T>::Vector(){};
    template<typename T> Vector<T>::Vector(T _x, T _y){x=_x; y=_y;}
    template<typename T> Vector<T>::~Vector(){};

    template<typename T> T Vector<T>::x() {return x;}
    template<typename T> T Vector<T>::y() {return y;}

    template<typename T> void Vector<T>::set(T _x,T _y) { tx = _x; ty = _y;}

    // assignments
    template<typename T> void Vector<T>::operator=(const Vector<T> &a) {tx = a.x(); ty = a.y();}
    template<typename T> void Vector<T>::operator+=(const Vector<T> &a){tx += a.x(); ty += a.y();}
    template<typename T> void Vector<T>::operator-=(const Vector<T> &a){tx -= a.x(); ty -= a.y();}
    template<typename T> void Vector<T>::operator*=(T a){tx *= a; ty *= a;}
    template<typename T> void Vector<T>::operator/=(T a){tx /= a; ty /= a;}


    template<typename T> Vector<T> operator+(const Vector<T> &a, const Vector<T> &b) { return Vector<T>(a.x()+b.x(), a.y()+b.y());}
    template<typename T> Vector<T> operator-(const Vector<T> &a, const Vector<T> &b) { return Vector<T>(a.x()-b.x(), a.y()-b.y());}

    template<typename T> Vector<T> operator-(const Vector<T> &a) { return Vector<T>(-a.x(), -a.y());}

    // operator*(const Vector<T> &a, T f);

    template<typename T> Vector<T> operator*(const Vector<T> &a, T f) { return Vector<T>(a.x()*f, a.y()*f);}
    template<typename T> Vector<T> operator*(T f, const Vector<T> &a) { return Vector<T>(a.x()*f, a.y()*f);}

    template<typename T> Vector<T> operator/(const Vector<T> &a, T f) { return Vector<T>(a.x()/f, a.y()/f);}
    template<typename T> Vector<T> operator/(T f, const Vector<T> &a) { return Vector<T>(a.x()/f, a.y()/f);}

    template<typename T> T operator*(const Vector<T> &a, const Vector<T> &b){ return (a.x()*b.x() + a.y()*b.y()); }

    template<typename T> void Vector<T>::norm() { T m = mag(); tx /= m; ty /= m;}
    template<typename T> void Vector<T>::setLength(T l){ norm(); tx *= l; ty *= l;}
    template<typename T> T Vector<T>::mag(){ return sqrt(tx*tx + ty*ty);}
}
