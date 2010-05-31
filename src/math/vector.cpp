#include "math/vector.h"

namespace math
{
    template<typename T> Vector<T>::Vector(){};
    template<typename T> Vector<T>::Vector(T _x, T _y){tx=_x; ty=_y;}
    template<typename T> Vector<T>::~Vector(){};

    template<typename T> T Vector<T>::getX() {return tx;}
    template<typename T> T Vector<T>::getY() {return ty;}

    template<typename T> void Vector<T>::set(T _x,T _y) { tx = _x; ty = _y;}

    // assignments
    template<typename T> void Vector<T>::operator=(const Vector<T> &a) {tx = a.getX(); ty = a.getY();}
    template<typename T> void Vector<T>::operator+=(const Vector<T> &a){tx += a.getX(); ty += a.getY();}
    template<typename T> void Vector<T>::operator-=(const Vector<T> &a){tx -= a.getX(); ty -= a.getY();}
    template<typename T> void Vector<T>::operator*=(T a){tx *= a; ty *= a;}
    template<typename T> void Vector<T>::operator/=(T a){tx /= a; ty /= a;}


    template<typename T> Vector<T> operator+(const Vector<T> &a, const Vector<T> &b) { return Vector<T>(a.getX()+b.getX(), a.getY()+b.getY());}
    template<typename T> Vector<T> operator-(const Vector<T> &a, const Vector<T> &b) { return Vector<T>(a.getX()-b.getX(), a.getY()-b.getY());}

    template<typename T> Vector<T> operator-(const Vector<T> &a) { return Vector<T>(-a.getX(), -a.getY());}

    // operator*(const Vector<T> &a, T f);

    template<typename T> Vector<T> operator*(const Vector<T> &a, T f) { return Vector<T>(a.getX()*f, a.getY()*f);}
    template<typename T> Vector<T> operator*(T f, const Vector<T> &a) { return Vector<T>(a.getX()*f, a.getY()*f);}

    template<typename T> Vector<T> operator/(const Vector<T> &a, T f) { return Vector<T>(a.getX()/f, a.getY()/f);}
    template<typename T> Vector<T> operator/(T f, const Vector<T> &a) { return Vector<T>(a.getX()/f, a.getY()/f);}

    template<typename T> T operator*(const Vector<T> &a, const Vector<T> &b){ return (a.getX()*b.getX() + a.getY()*b.getY()); }

    template<typename T> void Vector<T>::normalize() { setLength(1);}
    template<typename T> void Vector<T>::setLength(T l){ if(l == 1){return;}; normalize(); tx *= l; ty *= l;}
    template<typename T> T Vector<T>::length(){ return sqrt(tx*tx + ty*ty);}
}
