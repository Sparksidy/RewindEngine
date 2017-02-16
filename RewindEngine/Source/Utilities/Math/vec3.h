#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <iostream>

namespace math {

	template <class T = float> class vec3
	{
	public:
		T x, y, z;

		vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
		vec3() : x(0), y(0), z(0) {};
		vec3(const vec3<T>& rhs);

		vec3<T>& operator=(vec3<T> rhs);
		vec3<T>& operator+=(const vec3<T>& rhs);
		vec3<T>& operator-=(const vec3<T>& rhs);
		vec3<T>& operator*=(const vec3<T>& rhs);
		vec3<T>& operator*=(T rhs);
		vec3<T> operator+(const vec3<T>& rhs);
		vec3<T> operator-(const vec3<T>& rhs);
		vec3<T> operator*(const vec3<T>& rhs);
		vec3<T> operator*(T rhs);

		float length();
		float squaredLength();
		float distance(vec3<T>& rhs);
		float squaredDistance(vec3<T>& rhs);
		float dotProduct(vec3<T>& rhs);
		vec3<T> normalize();

		friend std::ostream& operator<<(std::ostream& out, const vec3<T>& rhs)
		{
			out << rhs.x << " " << rhs.y << " " << rhs.z << std::endl;

			return out;
		}
	};

	template <class T>
	vec3<T>::vec3(const vec3<T>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {};

	template <class T>
	inline vec3<T>& vec3<T>::operator=(vec3<T> rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	template <class T>
	inline vec3<T>& vec3<T>::operator+=(const vec3<T>& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	template <class T>
	inline vec3<T>& vec3<T>::operator-=(const vec3<T>& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	template <class T>
	inline vec3<T>& vec3<T>::operator*=(const vec3<T>& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	template <class T>
	inline vec3<T>& vec3<T>::operator*=(T rhs)
	{
		x = x*rhs;
		y = y*rhs;
		z = z*rhs;
		return *this;
	}

	template <class T>
	inline vec3<T> vec3<T>::operator+(const vec3<T>& rhs)
	{
		vec3<T> res(rhs.x + x, rhs.y + y, rhs.z + z);
		return res;
	}

	template <class T>
	inline vec3<T> vec3<T>::operator-(const vec3<T>& rhs)
	{
		vec3<T> res(rhs.x - x, rhs.y - y, rhs.z - z);
		return res;
	}

	template <class T>
	inline vec3<T> vec3<T>::operator*(const vec3<T>& rhs)
	{
		vec3<T> res(rhs.x * x, rhs.y * y, rhs.z * z);
		return res;
	}

	template <class T>
	inline vec3<T> vec3<T>::operator*(T rhs)
	{
		vec3<T> res(rhs * x, rhs * y, rhs * z);
		return res;
	}

	template <class T>
	inline float vec3<T>::length()
	{
		return sqrt(x*x + y*y + z*z);
	}

	template <class T>
	inline float vec3<T>::squaredLength()
	{
		return x*x + y*y + z*z;
	}

	template <class T>
	inline float vec3<T>::distance(vec3<T>& rhs)
	{
		return sqrt((x - rhs.x)*(x - rhs.x) + (y - rhs.y)*(y - rhs.y) + (z - rhs.z)*(z - rhs.z));
	}

	template <class T>
	inline float vec3<T>::squaredDistance(vec3<T>& rhs)
	{
		return (x - rhs.x)*(x - rhs.x) + (y - rhs.y)*(y - rhs.y) + (z - rhs.z)*(z - rhs.z);
	}

	template<class T>
	inline float vec3<T>::dotProduct(vec3<T>& rhs)
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	template <class T>
	vec3<T> vec3<T>::normalize()
	{
		T length = this->length();
		vec3<T> res(x / length, y / length, z / length);
		
		return res;
	}
}

#endif // !VEC3H