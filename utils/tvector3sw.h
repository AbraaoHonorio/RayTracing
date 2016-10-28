/*
 * tvector3sw.h
 *
 * Copyright (c) 2013 Christian Azambuja Pagot
 */

#ifndef __TVECTOR3SW_H__
#define __TVECTOR3SW_H__

#include <math.h>

template <class T> class TVector3Sw
{
	public:
		TVector3Sw();
		TVector3Sw(T a, T b, T c);
		TVector3Sw(const TVector3Sw<T>& a);
		~TVector3Sw(){};

		const TVector3Sw<T> operator + () const;
	    TVector3Sw<T> operator - () const;

		template <class S> friend TVector3Sw<T> operator + (const TVector3Sw<T>& rhs, const TVector3Sw<T>& lhs);
		template <class S> friend TVector3Sw<T> operator - (const TVector3Sw<T>& rhs, const TVector3Sw<T>& lhs);

		TVector3Sw<T>& operator  = (const TVector3Sw<T>& rhs);
		TVector3Sw<T>& operator += (const TVector3Sw<T>& rhs);
		TVector3Sw<T>& operator -= (const TVector3Sw<T>& rhs);
		TVector3Sw<T>& operator *= (const T& rhs);
		TVector3Sw<T>& operator /= (const T& rhs);

		T operator [] (unsigned int index) const;

		T e[3];
};

//---------------------------------------------------------------------------
template <class T> TVector3Sw<T>::TVector3Sw()
{
	this->e[0] = 0.0;
	this->e[1] = 0.0;
	this->e[2] = 0.0;
}

//---------------------------------------------------------------------------
template <class T> TVector3Sw<T>::TVector3Sw(T a, T b, T c)
{
	this->e[0] = a;
	this->e[1] = b;
	this->e[2] = c;
}

//---------------------------------------------------------------------------
template <class T> TVector3Sw<T>::TVector3Sw(const TVector3Sw<T>& a)
{
	this->e[0] = a.e[0];
	this->e[1] = a.e[1];
	this->e[2] = a.e[2];
}

//---------------------------------------------------------------------------
template <class T> inline const TVector3Sw<T> TVector3Sw<T>::operator + () const 
{
	return *this;
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T> TVector3Sw<T>::operator - () const 
{
	return TVector3Sw<T>(-this->e[0], -this->e[1], -this->e[2]);
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T>& TVector3Sw<T>::operator += (const TVector3Sw<T>& rhs)
{
	this->e[0] += rhs.e[0];
	this->e[1] += rhs.e[1];
	this->e[2] += rhs.e[2];

	return *this;
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T>& TVector3Sw<T>::operator -= (const TVector3Sw<T>& rhs)
{
	this->e[0] -= rhs.e[0];
	this->e[1] -= rhs.e[1];
	this->e[2] -= rhs.e[2];

	return *this;
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T>& TVector3Sw<T>::operator *= (const T& rhs)
{
	this->e[0] *= rhs;
	this->e[1] *= rhs;
	this->e[2] *= rhs;

	return *this;
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T>& TVector3Sw<T>::operator /= (const T& rhs)
{
	this->e[0] /= rhs;
	this->e[1] /= rhs;
	this->e[2] /= rhs;

	return *this;
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T> operator + (const TVector3Sw<T>& lhs, const TVector3Sw<T>& rhs)
{
	return TVector3Sw<T>(lhs) += rhs;
}

//---------------------------------------------------------------------------
template <class T, class U> inline TVector3Sw<T> operator * (const TVector3Sw<T>& lhs, const U& rhs)
{
	return TVector3Sw<T>(lhs) *= rhs;
}

//---------------------------------------------------------------------------
template <class T, class U> inline TVector3Sw<T> operator * (const U& lhs, const TVector3Sw<T>& rhs)
{
	return TVector3Sw<T>(rhs) *= lhs;
}

//---------------------------------------------------------------------------
template <class T, class U> inline TVector3Sw<T> operator / (const TVector3Sw<T>& lhs, const U& rhs)
{
	return TVector3Sw<T>(lhs) /= rhs;
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T> operator - (const TVector3Sw<T>& rhs, const TVector3Sw<T>& lhs)
{
	return TVector3Sw<T>(rhs) -= lhs;
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T>& TVector3Sw<T>::operator = (const TVector3Sw<T>& rhs)
{
	if (this->e[0] != rhs.e[0])
		this->e[0] = rhs.e[0];

	if (this->e[1] != rhs.e[1])
		this->e[1] = rhs.e[1];

	if (this->e[2] != rhs.e[2])
		this->e[2] = rhs.e[2];

	return *this;
}

//---------------------------------------------------------------------------
template <class T> inline T TVector3Sw<T>::operator [] (unsigned int index) const
{ 
	return this->e[index];
} 

//---------------------------------------------------------------------------
template <class T> inline T dot(const TVector3Sw<T>& a, const TVector3Sw<T>& b)
{
    return a.e[0] * b.e[0] + 
           a.e[1] * b.e[1] +
           a.e[2] * b.e[2];
}

//---------------------------------------------------------------------------
template <class T> inline T sqr(const TVector3Sw<T>& a)
{
    return dot(a, a);
}

//---------------------------------------------------------------------------
template <class T> inline T mag(const TVector3Sw<T>& a)
{
    return sqrt(dot(a, a));
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T> normal(const TVector3Sw<T>& a)
{
    return a / mag(a); 
}

//---------------------------------------------------------------------------
template <class T> inline TVector3Sw<T> cross(const TVector3Sw<T>& a, const TVector3Sw<T>& b)
{
    return TVector3Sw<T>( a.e[1] * b.e[2] - a.e[2] * b.e[1],
                          a.e[2] * b.e[0] - a.e[0] * b.e[2],
                          a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}

#endif // __TVECTOR3SW_H__

