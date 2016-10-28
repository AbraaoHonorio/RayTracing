#include "ray.h"

//------------------------------------------------------------------------------
TRay::TRay()
{ }

//------------------------------------------------------------------------------
TRay::~TRay()
{ }

//------------------------------------------------------------------------------
TRay::TRay(TVector3 o, TVector3 d)
{
	this->ray[0] = o;
	this->ray[1] = d;
}

//------------------------------------------------------------------------------
TVector3 TRay::getOrigin() const
{
	return this->ray[0];
}

//------------------------------------------------------------------------------
TVector3 TRay::getDirection() const
{
	return this->ray[1];
}

//------------------------------------------------------------------------------
TVector3 TRay::getPointAtParameter(const float t) const
{
	return this->ray[0] + t * this->ray[1];
}

//------------------------------------------------------------------------------
void TRay::PrintOrigin(void)
{
	//std::clog << "[" << this->ray[0][0] << ", " << this->ray[0][1] << ", "
	//		<< this->ray[0][2] << "]";
}

//------------------------------------------------------------------------------
void TRay::PrintDirection(void)
{
	printf("[%f, %f, %f]", ray[1][0], ray[1][1], ray[1][2]);
}

//------------------------------------------------------------------------------
TRay TRay::operator=(TRay r)
{
	this->ray[0] = r.getOrigin();
	this->ray[1] = r.getDirection();

	return *this;
}

//------------------------------------------------------------------------------
bool TRay::hit(TTriangle t, float& d)
{
	float det, inv_det;
	float u, v;
	TVector3 edge1, edge2;
	TVector3 pvec, tvec, qvec;

	edge1 = t.v[1] - t.v[0];
	edge2 = t.v[2] - t.v[0];

	pvec = cross(ray[1], edge2);

	det = dot(edge1, pvec);

	if (det < EPSILON)
		return 0;

	tvec = ray[0] - t.v[0];

	u = dot(tvec, pvec);
	if ((u < 0.0) || (u > det))
		return 0;

	qvec = cross(tvec, edge1);

	v = dot(ray[1], qvec);
	if ((v < 0.0) || (u + v > det))
		return 0;

	d = dot(edge2, qvec);
	inv_det = 1.0 / det;

	d *= inv_det;
	//d = 0.5f;

	if (d < 0.001)
		return 0;

	if ((det > -EPSILON) && (det < EPSILON))
		return 0;

	inv_det = 1.0f / det;
	tvec = ray[0] - t.v[0];

	u = dot(tvec, pvec) * inv_det;
	if ((u < 0.0f) || (u > 1.0f))
		return 0;

	qvec = cross(tvec, edge1);

	v = dot(ray[1], qvec) * inv_det;
	if ((v < 0.0f) || (u + v > 1.0f))
		return 0;

	d = dot(edge2, qvec) * inv_det;
	//d = 0.5f;

	if (d < 0.001)
		return 0;

	//fprintf(stderr,"===> %f\n", d);
	return 1;
}
