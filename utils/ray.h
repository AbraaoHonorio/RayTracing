/*
 * ray.h
 *
 *  Created on: Oct 28, 2014
 *      This code is based on the code presented in the book
 *      "Realistic Ray Tracing", 3rd. Edition
 *      Peter Shirley and R. Keith Morley
 */

#ifndef RAY_RAY_H_
#define RAY_RAY_H_

#include "triangle.h"
#include <stdio.h>

class TRay
{
private:
public:
	TRay();
	TRay(TVector3 o, TVector3 d);
	~TRay();
	TVector3 getOrigin() const;
	TVector3 getDirection() const;
	TVector3 getPointAtParameter(const float t) const;
	void PrintOrigin(void);
	void PrintDirection(void);
	TRay operator=(TRay r);
	bool hit(TTriangle t, float& d);

	TVector3 ray[2];
};

#endif /* RAY_RAY_H_ */
