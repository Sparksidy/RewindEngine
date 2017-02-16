#ifndef MAT3
#define MAT3

#include "vec2.h"
#include <math.h>
#define M_PI 3.14159265358979323846

namespace math {

	template <class T = float> class mat3
	{
	public:
		T m[3][3];
		mat3();
		mat3(const mat3<T>& rhs);

		mat3<T>& operator=(mat3<T> rhs);
		mat3<T>& operator+=(const mat3<T>& rhs);
		mat3<T>& operator-=(const mat3<T>& rhs);
		mat3<T>& operator*=(const mat3<T>& rhs);
		mat3<T>& operator*=(T rhs);
		mat3<T> operator+(const mat3<T>& rhs);
		mat3<T> operator-(const mat3<T>& rhs);
		mat3<T> operator*(const mat3<T>& rhs);
		mat3<T> operator*(T rhs);

		void identity();
		
		static mat3<T> translate(double x, double y)
		{
			mat3<T> res;
			res.identity();
			res.m[0][2] = x;
			res.m[1][2] = y;
			return res;
		};

		static mat3<T> rotateByDegree(double angle)
		{
			mat3<T> res;
			res.identity();
			res.m[0][0] = cos(angle * M_PI / 180.0);
			res.m[0][1] = -sin(angle * M_PI / 180.0);
			res.m[1][0] = sin(angle * M_PI / 180.0);
			res.m[1][1] = cos(angle * M_PI / 180.0);
			return res;
		};

		static mat3<T> rotateByRadians(double radians)
		{
			mat3<T> res;
			res.identity();
			res.m[0][0] = cos(radians);
			res.m[0][1] = -sin(radians);
			res.m[1][0] = sin(radians);
			res.m[1][1] = cos(radians);
			return res;
		};

		static mat3<T> scale(double x, double y)
		{
			mat3<T> res;
			res.identity();
			res.m[0][0] = x;
			res.m[1][1] = y;
			return res;
		};

		static vec2<T> mat3x3byVec2(mat3<T> mat, vec2<T> vec)
		{
			vec2<T> res;
			float temp[3];
			float Vector3D[3];
			Vector3D[0] = vec.x;
			Vector3D[1] = vec.y;
			Vector3D[2] = 1;

			for (int i = 0; i < 3; i++)
			{
				temp[i] = 0;
				for (int j = 0; j < 3; j++)
					temp[i] += Vector3D[j] * mat.m[i][j];
			}

			res.x = temp[0];
			res.y = temp[1];

			return res;
		}
	};

	template <class T>
	mat3<T>::mat3()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] = (i==j)?1.0f:0.0f;
	}

	template <class T>
	mat3<T>::mat3(const mat3<T>& rhs)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] = rhs.m[i][j];
	}

	template <class T>
	mat3<T>& mat3<T>::operator=(mat3<T> rhs)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] = rhs.m[i][j];
		return *this;
	}

	template <class T>
	mat3<T>& mat3<T>::operator+=(const mat3<T>& rhs)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] += rhs.m[i][j];
		return *this;
	}


	template <class T>
	mat3<T>& mat3<T>::operator-=(const mat3<T>& rhs)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] -= rhs.m[i][j];
		return *this;
	}

	template <class T>
	mat3<T>& mat3<T>::operator*=(const mat3<T>& rhs)
	{
		mat3<T> res;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				res.m[i][j] = 0;
				for (int k = 0; k < 3; k++)
					res.m[i][j] += m[i][k] * rhs.m[k][j];
			}
		*this = res;
		return *this;
	}

	template <class T>
	mat3<T>& mat3<T>::operator*=(T rhs)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m[i][j] = m[i][j] * rhs;
		return *this;
	}

	template <class T>
	mat3<T> mat3<T>::operator+(const mat3<T>& rhs)
	{
		mat3<T> res;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				res.m[i][j] = m[i][j] + rhs.m[i][j];
		return res;
	}

	template <class T>
	mat3<T> mat3<T>::operator-(const mat3<T>& rhs)
	{
		mat3<T> res;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				res.m[i][j] = m[i][j] - rhs.m[i][j];
		return res;
	}

	template <class T>
	mat3<T> mat3<T>::operator*(const mat3<T>& rhs)
	{
		mat3<T> res;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				res.m[i][j] = 0;
				for (int k = 0; k < 3; k++)
					res.m[i][j] += m[i][k] * rhs.m[k][j];
			}
		return res;
	}

	template <class T>
	mat3<T> mat3<T>::operator*(T rhs)
	{
		mat3<T> res;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				res[i][j] = m[i][j] * rhs;
		return res;
	}

	template <class T>
	void mat3<T>::identity()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->m[i][j] = (i == j) ? 1.0f : 0.0f;
	}

}


#endif // !MAT3