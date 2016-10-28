#include "camera.h"

//------------------------------------------------------------------------------
TCamera::TCamera()
{ }

//------------------------------------------------------------------------------
TCamera::~TCamera()
{ }

//------------------------------------------------------------------------------
TCamera::TCamera(const TVector3 &position,
	   		 	 const TVector3 &lookat,
				 const TVector3 &up,
			     const float &aspect,
				 const float &distance,
				 int image_width,
				 int image_height)
{
	TVector3 w;

	m_position	= position;
	m_up    	= up;
	m_lookat	= lookat;
	m_direction	= normal(m_lookat - m_position);
	m_u0    	= -aspect / 2.0f;
	m_u1    	=  aspect / 2.0f;
	m_v0     	=  0.5f;
	m_v1    	= -0.5f;
	m_distance	= distance;
	m_image_width = image_width;
	m_image_height = image_height;

	w = -m_direction;

	m_uvw.initFromUW(normal(cross(m_up, w)), w);
}

//------------------------------------------------------------------------------
TRay TCamera::getRay(float x, float y)
{
	TVector3 u, v;
    TVector3 origin, target;

	x = (float) x / (float) m_image_width;
	y = (float) y / (float) m_image_height;

	u = (m_u1 - m_u0) * m_uvw.getU();
	v = (m_v1 - m_v0) * m_uvw.getV();

	m_corner = 	m_u0 * m_uvw.getU() +
				m_v0 * m_uvw.getV() -
				m_distance * m_uvw.getW();

	origin = m_position;
	target = normal(m_corner + u*x + v*y);

	return TRay(origin,target);
}
