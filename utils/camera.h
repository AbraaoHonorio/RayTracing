/*
 * camera.h
 *
 *  Created on: Oct 28, 2014
 *      This code is based on the code presented in the book
 *      "Realistic Ray Tracing", 3rd. Edition
 *      Peter Shirley and R. Keith Morley
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"
#include "tonb.h"

class TCamera
{
    public:
	    TCamera();
	    TCamera(const TVector3 &position,
				const TVector3 &lookat,
				const TVector3 &up,
				const float &aspect,
				const float &distance,
				int image_width,
				int image_height);
	    ~TCamera();

	    TRay getRay(float x, float y);

	private:
	    TVector3 m_position;
		TVector3 m_lookat;
		TVector3 m_direction;
		TVector3 m_up;
		TVector3 m_corner;
		float m_distance;
	    float m_u0;
		float m_u1;
		float m_v0;
		float m_v1;
		int m_image_width;
		int m_image_height;
	    TONB m_uvw;
};

#endif /* CAMERA_H_ */
