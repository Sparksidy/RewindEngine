#pragma once

#include "vec3.h"
#include <math.h>
#define M_PI 3.14159265358979323846

namespace math {

	template <class T = float> class mat4
	{
	public:
		T m[4][4];
		mat4();
		mat4(const mat4<T>& rhs);

		mat4<T>& operator=(mat4<T> rhs);
		mat4<T>& operator+=(const mat4<T>& rhs);
		mat4<T>& operator-=(const mat4<T>& rhs);
		mat4<T>& operator*=(const mat4<T>& rhs);
		mat4<T>& operator*=(T rhs);
		mat4<T> operator+(const mat4<T>& rhs);
		mat4<T> operator-(const mat4<T>& rhs);
		mat4<T> operator*(const mat4<T>& rhs);
		mat4<T> operator*(T rhs);

		void identity();
		
		static mat4<T> translate(T x, T y, T z)
		{
			mat4<T> res;
			res.identity();
			res.m[0][3] = x;
			res.m[1][3] = y;
			res.m[2][3] = z;
			return res;
		};

		static mat4<T> rotateByDegree(T angle)
		{
			mat4<T> res;
			res.identity();
			res.m[0][0] = cos(angle * M_PI / 180.0);
			res.m[0][1] = -sin(angle * M_PI / 180.0);
			res.m[1][0] = sin(angle * M_PI / 180.0);
			res.m[1][1] = cos(angle * M_PI / 180.0);
			return res;
		};

		static mat4<T> rotateByRadians(double radians)
		{
			mat4<T> res;
			res.identity();
			res.m[0][0] = cos(radians);
			res.m[0][1] = -sin(radians);
			res.m[1][0] = sin(radians);
			res.m[1][1] = cos(radians);
			return res;
		};

		static mat4<T> scale(T x, T y, T z)
		{
			mat4<T> res;
			res.identity();
			res.m[0][0] = x;
			res.m[1][1] = y;
			res.m[2][2] = z;
			return res;
		};

		static vec3<T> mat4x4byVec3(mat4<T> mat, vec3<T> vec)
		{
			vec3<T> res;
			float temp[4];
			float Vector4D[4];
			Vector4D[0] = vec.x;
			Vector4D[1] = vec.y;
			Vector4D[2] = vec.z;
			Vector4D[3] = 1;

			for (int i = 0; i < 4; i++)
			{
				temp[i] = 0;
				for (int j = 0; j < 4; j++)
					temp[i] += Vector4D[j] * mat.m[i][j];
			}

			res.x = temp[0];
			res.y = temp[1];
			res.z = temp[2];

			return res;
		}
	};

	template <class T>
	mat4<T>::mat4()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] = (i == j) ? 1.0f:0.0f;
	}

	template <class T>
	mat4<T>::mat4(const mat4<T>& rhs)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] = rhs.m[i][j];
	}

	template <class T>
	mat4<T>& mat4<T>::operator=(mat4<T> rhs)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] = rhs.m[i][j];
		return *this;
	}

	template <class T>
	mat4<T>& mat4<T>::operator+=(const mat4<T>& rhs)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] += rhs.m[i][j];
		return *this;
	}


	template <class T>
	mat4<T>& mat4<T>::operator-=(const mat4<T>& rhs)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] -= rhs.m[i][j];
		return *this;
	}

	template <class T>
	mat4<T>& mat4<T>::operator*=(const mat4<T>& rhs)
	{
		mat4<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				res.m[i][j] = 0;
				for (int k = 0; k < 3; k++)
					res.m[i][j] += m[i][k] * rhs.m[k][j];
			}
		*this = res;
		return *this;
	}

	template <class T>
	mat4<T>& mat4<T>::operator*=(T rhs)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				m[i][j] = m[i][j] * rhs;
		return *this;
	}

	template <class T>
	mat4<T> mat4<T>::operator+(const mat4<T>& rhs)
	{
		mat4<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res.m[i][j] = m[i][j] + rhs.m[i][j];
		return res;
	}

	template <class T>
	mat4<T> mat4<T>::operator-(const mat4<T>& rhs)
	{
		mat4<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res.m[i][j] = m[i][j] - rhs.m[i][j];
		return res;
	}

	template <class T>
	mat4<T> mat4<T>::operator*(const mat4<T>& rhs)
	{
		mat4<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				res.m[i][j] = 0;
				for (int k = 0; k < 4; k++)
					res.m[i][j] += m[i][k] * rhs.m[k][j];
			}
		return res;
	}

	template <class T>
	mat4<T> mat4<T>::operator*(T rhs)
	{
		mat4<T> res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res[i][j] = m[i][j] * rhs;
		return res;
	}

	template <class T>
	void mat4<T>::identity()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->m[i][j] = (i == j) ? 1.0f : 0.0f;
	}

}