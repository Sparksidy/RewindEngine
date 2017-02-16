#include <iostream>
#include "vec3.h"
#include "vec2.h"
#include "mat3.h"

int main()
{
	//Declaration of vec2
	math::vec2<> d1; //d1 = (0,0)

	math::vec3<> t0;

	math::vec2<> i1(0,2); //i1 = (0,2)

	math::vec2<> d2(i1); //d2 = (0.0f, 2,0f)

	math::vec2<> d3(0.1,0.1); //d3 = (0.1f, 0.1f)

	math::vec2<> i2(d3); //i2 = (0, 0)

	d1.x = 1.5; //direct access

	d1 = d2 * d3 + i1; //works only with vec3 (2, 2) * (1, 2) = (2, 4)
	d1 += i1; //works only with vec3
	
	d2 *= 2; //works both for vec3 and built-in types (1, 3) * 2 = (2, 6)
	d2 *= d2; //(1, 2) * (1, 2) = (1, 9)

	math::vec2<> d4(3, 10);

	double s = d4.length(); //length, squaredLength also available
	d3 = d4.normalize(); //normalize

	s = d3.distance(i1); //distance, squaredDistance also available

	std::cout << d2 << std::endl; //cout
	

	//Everything is the same for vec3

	//Declaration of mat3
	math::mat3<> m1;
	m1.m[0][0] = 1;
	m1.m[0][1] = 3;
	m1.m[0][2] = 5;
	m1.m[1][0] = 8;
	m1.m[1][1] = -8;
	m1.m[1][2] = 88;
	m1.m[2][1] = 78;

	math::mat3<> m2;
	m2.m[0][0] = 1;
	m2.m[0][1] = 2;
	m2.m[0][2] = 3;
	m2.m[1][0] = 4;
	m2.m[1][1] = 5;
	m2.m[1][2] = 6;
	m2.m[2][1] = 7;

	math::mat3<> m3;
	m1 = m2 + m2;
	/*1 0 0	  0 0 1   1 0 1
	  0 1 0 + 0 1 0 = 0 2 0
      0 0 1	  1 0 0   1 0 1*/
	m1 = m1 - m2;
	m1 -= m2;
	m1 *= m2;
	m3 = m1 * m2;
	m3 *= 2;

	math::mat3<> m4;
	m4.identity(); //set m4 to id

	math::vec2<> t(3, 10);

	//getting SRT matrices
	m1 = math::mat3<>::translate(10, 20);

	m2 = math::mat3<>::scale(25, 20);

	m3 = math::mat3<>::rotateByDegree(90);

	m4 = math::mat3<>::rotateByRadians(M_PI/2);

	//multiply 3x3 by 2d vector with homogeneous coordinate
	d1 = math::mat3<>::mat3x3byVec2(m1, d4);

    return 0;
}

