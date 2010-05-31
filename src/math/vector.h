#ifndef SLC_MATH_VECTOR_H
#define SLC_MATH_VECTOR_H

#include <cmath>

#include "math/vector_fwd.h"

namespace math{

  // note: there's some sweet Boost class you can extend to autoamtically create a bunch of operators
  //  look into it!
  template<typename T>
  class Vector
  {
    public:

    Vector();
    Vector(T x, T y);
    ~Vector();

    // assignments
    template<typename T2>
    void operator=(const Vector<T2> &a){ tx = a.getX(); ty = a.getY();}
    template<typename T2>
    void operator+=(const Vector<T2> &a){ tx += a.getX(); ty += a.getY();}
    template<typename T2>
    void operator-=(const Vector<T2> &a){ tx -= a.getX(); ty -= a.getY();}
    template<typename T2>
    void operator*=(T2 a){tx *= a; ty *= a;}
    // FIXME: dividing a number from a vector sounds weird to me ;z33ky
    template<typename T2>
    void operator/=(T2 a){tx /= a; ty /= a;}

    void normalize(){ setLength<T>(1); }
    // FIXME: should those two length-method not always use a floating-point type? ;z33ky
    template<typename T2>
    void setLength(T2 len);
    T lengthSqr(){ return x * x + y * y;}
    T length(){ return std::sqrt(lengthSqr());}

    template<typename T2>
    T distanceSqr(const Vector<T2> &a){ return ((*this) - a).lengthSqr();}
    template<typename T2>
    T distance(const Vector<T2> &a){ return std::sqrt(distanceSqr());}

    T getX() const{ return tx;}
    void setX(T x){ tx = x;}
    T getY() const{ return ty;}
    void setY(T y){ ty = y;}

    void set(T, T){ tx = x; ty = y;}

    private:
    T tx;
    T ty;
  };

  // addition, subtraction and negation
  template<typename T, typename T2>
  Vector<T> operator+(const Vector<T> &a, const Vector<T2> &b);

  template<typename T, typename T2>
  Vector<T> operator-(const Vector<T> &a, const Vector<T2> &b);

  template<typename T>
  Vector<T> operator-(const Vector<T> &a);

  // multiplication
  template<typename T, typename T2>
  Vector<T> operator*(const Vector<T> &a, T2 f);

  template<typename T, typename T2>
  Vector<T> operator*(T2 f, const Vector<T> &a);

  // division
  template<typename T, typename T2>
  Vector<T> operator/(const Vector<T>&a, T2 f);

  template<typename T, typename T2>
  Vector<T> operator/(T2 f, const Vector<T> &a);

  // dot
  template<typename T, typename T2>
  T operator*(const Vector<T> &a, const Vector<T2> &b);

  #include "vector.inl"

}
#endif
