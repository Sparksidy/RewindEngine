#ifndef VEC2H
#define VEC2H

#include <math.h>
#include <iostream>

namespace math {

	template <class T = float> class vec2
	{
	public:
		T x, y;

		vec2(T _x, T _y) : x(_x), y(_y) {};
		vec2() : x(0), y(0) {};
		vec2(const vec2<T>& rhs);

		vec2<T>& operator=(vec2<T> rhs);
		vec2<T>& operator+=(const vec2<T>& rhs);
		vec2<T>& operator-=(const vec2<T>& rhs);
		vec2<T>& operator*=(const vec2<T>& rhs);
		vec2<T>& operator*=(T rhs);
		vec2<T> operator+(const vec2<T>& rhs);
		vec2<T> operator-(const vec2<T>& rhs);
		vec2<T> operator*(const vec2<T>& rhs);
		vec2<T> operator*(T rhs);

		float length();
		float squaredLength();
		float distance(vec2<T>& rhs);
		float squaredDistance(vec2<T>& rhs);
		float dotProduct(vec2<T>& rhs);
		vec2<T> normalize();

		friend std::ostream& operator<<(std::ostream& out, const vec2<T>& rhs)
		{
			out << rhs.x << " " << rhs.y << std::endl;

			return out;
		}
	};

	template <class T>
	vec2<T>::vec2(const vec2<T>& rhs) : x(rhs.x), y(rhs.y) {};

	template <class T>
	inline vec2<T>& vec2<T>::operator=(vec2<T> rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	template <class T>
	inline vec2<T>& vec2<T>::operator+=(const vec2<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	template <class T>
	inline vec2<T>& vec2<T>::operator-=(const vec2<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	template <class T>
	inline vec2<T>& vec2<T>::operator*=(const vec2<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	template <class T>
	inline vec2<T>& vec2<T>::operator*=(T rhs)
	{
		x = x*rhs;
		y = y*rhs;
		return *this;
	}

	template <class T>
	inline vec2<T> vec2<T>::operator+(const vec2<T>& rhs)
	{
		vec2<T> res(rhs.x + x, rhs.y + y);
		return res;
	}

	template <class T>
	inline vec2<T> vec2<T>::operator-(const vec2<T>& rhs)
	{
		vec2<T> res(rhs.x - x, rhs.y - y);
		return res;
	}

	template <class T>
	inline vec2<T> vec2<T>::operator*(const vec2<T>& rhs)
	{
		vec2<T> res(rhs.x * x, rhs.y * y);
		return res;
	}

	template <class T>
	inline vec2<T> vec2<T>::operator*(T rhs)
	{
		vec2<T> res(rhs * x, rhs * y);
		return res;
	}

	template <class T>
	inline float vec2<T>::length()
	{
		return sqrt(x*x + y*y);
	}

	template <class T>
	inline float vec2<T>::squaredLength()
	{
		return x*x + y*y;
	}

	template <class T>
	inline float vec2<T>::distance(vec2<T>& rhs)
	{
		return sqrt((x - rhs.x)*(x - rhs.x) + (y - rhs.y)*(y - rhs.y));
	}

	template <class T>
	inline float vec2<T>::squaredDistance(vec2<T>& rhs)
	{
		return (x - rhs.x)*(x - rhs.x) + (y - rhs.y)*(y - rhs.y);
	}

	template<class T>
	inline float vec2<T>::dotProduct(vec2<T>& rhs)
	{
		return x * rhs.x + y * rhs.y;
	}

	template <class T>
	vec2<T> vec2<T>::normalize()
	{
		T length = this->length();
		vec2<T> res(x / length, y / length);
		
		return res;
	}
}

#endif // !VEC2H