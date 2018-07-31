#ifndef  MATH3D_H
#define MATH3D_H

#include<stdint.h>
#include<math.h>
#include<vector>

struct  Vector3f
{
	float x;
	float y;
	float z;

	Vector3f() {}

	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f(const float *PFloat)
	{
		//传入的是数组
		x = PFloat[0];
		y = PFloat[0];
		z = PFloat[0];

	}
	Vector3f(const float f)
	{
		x = y = z = f;
	}

	///<summary>
	///重载运算符号+=
	///</summary>
	Vector3f & operator+=(const Vector3f & r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		//返回 this 是本身的指针， 引用必须赋值 所有返回他的引用 也可以返回 *
		return *this;
	}

	///<summary>
	///重载运算符号-=
	///</summary>
	Vector3f & operator-=(const Vector3f &r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	///<summary>
	///重载运算符号*=
	///const 作函数参数
	///</summary>
	Vector3f & operator*=(const Vector3f &r)
	{
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	///<summary>
	///类型转换函数
	///</summary>
	operator const float *() const
	{
		return &(x);
	}
	///<summary>
	///输出函数
	///</summary>
	void Print() const
	{
		printf("(%.02f,%.02f,%.02f)", x, y, z);
	}

};

///<summary>
///内联函数
///</summary>
inline Vector3f operator+(const Vector3f &l, const Vector3f &r)
{
	Vector3f Ret(l.x + r.x, l.y + r.y, l.z + r.z);
	return Ret;
}

///<summary>
///内联函数
///</summary>
inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}
///<summary>
///内联函数
///</summary>
inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}

///<summary>
///内联函数
///</summary>
inline Vector3f operator/(const Vector3f& l, float f)
{
	Vector3f Ret(l.x / f,
		l.y / f,
		l.z / f);

	return Ret;
}
#endif // ! MATH3D_H

