template<typename T>
Vector<T>::Vector(){}

template<typename T>
Vector<T>::Vector(T x, T y)
  :tx(x), ty(y){}

template<typename T>
Vector<T>::~Vector(){}

template<typename T> template<typename T2>
void Vector<T>::setLength(T2 len)
{
  T scale = len * len / lengthSqr();
  tx *= scale;
  ty *= scale;
}

template<typename T> template <typename T2>
Vector<T>::operator sf::Vector2<T2>()
{
  return sf::Vector2<T2>( tx, ty );
}

template<typename T, typename T2>
Vector<T> operator+(const Vector<T> &a, const Vector<T2> &b)
{
  return Vector<T>(a.getX()+b.getX(), a.getY()+b.getY());
}

template<typename T, typename T2>
Vector<T> operator-(const Vector<T> &a, const Vector<T2> &b)
{
  return Vector<T>(a.getX()-b.getX(), a.getY()-b.getY());
}

template<typename T>
Vector<T> operator-(const Vector<T> &a)
{
  return Vector<T>(-a.getX(), -a.getY());
}

// operator*(const Vector<T> &a, T f);

template<typename T, typename T2>
Vector<T> operator*(const Vector<T> &a, T2 f)
{
  return Vector<T>(a.getX()*f, a.getY()*f);
}

template<typename T, typename T2>
Vector<T> operator*(T2 f, const Vector<T> &a)
{
  return Vector<T>(a.getX()*f, a.getY()*f);
}

template<typename T, typename T2>
Vector<T> operator/(const Vector<T> &a, T2 f)
{
  return Vector<T>(a.getX()/f, a.getY()/f);
}

template<typename T, typename T2>
Vector<T> operator/(T2 f, const Vector<T> &a)
{
  return Vector<T>(a.getX()/f, a.getY()/f);
}

template<typename T, typename T2>
T operator*(const Vector<T> &a, const Vector<T2> &b)
{
  return (a.getX()*b.getX() + a.getY()*b.getY());
}
