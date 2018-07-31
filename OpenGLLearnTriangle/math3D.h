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
		//�����������
		x = PFloat[0];
		y = PFloat[0];
		z = PFloat[0];

	}
	Vector3f(const float f)
	{
		x = y = z = f;
	}

	///<summary>
	///�����������+=
	///</summary>
	Vector3f & operator+=(const Vector3f & r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		//���� this �Ǳ����ָ�룬 ���ñ��븳ֵ ���з����������� Ҳ���Է��� *
		return *this;
	}

	///<summary>
	///�����������-=
	///</summary>
	Vector3f & operator-=(const Vector3f &r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	///<summary>
	///�����������*=
	///const ����������
	///</summary>
	Vector3f & operator*=(const Vector3f &r)
	{
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	///<summary>
	///����ת������
	///</summary>
	operator const float *() const
	{
		return &(x);
	}
	///<summary>
	///�������
	///</summary>
	void Print() const
	{
		printf("(%.02f,%.02f,%.02f)", x, y, z);
	}

};

///<summary>
///��������
///</summary>
inline Vector3f operator+(const Vector3f &l, const Vector3f &r)
{
	Vector3f Ret(l.x + r.x, l.y + r.y, l.z + r.z);
	return Ret;
}

///<summary>
///��������
///</summary>
inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);

	return Ret;
}
///<summary>
///��������
///</summary>
inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);

	return Ret;
}

///<summary>
///��������
///</summary>
inline Vector3f operator/(const Vector3f& l, float f)
{
	Vector3f Ret(l.x / f,
		l.y / f,
		l.z / f);

	return Ret;
}
#endif // ! MATH3D_H

