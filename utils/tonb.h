/*
 * tonb.h
 *
 *  Created on: Oct 28, 2014
 *      This code is based on the code presented in the book
 *      "Realistic Ray Tracing", 3rd. Edition
 *      Peter Shirley and R. Keith Morley
 */

#ifndef _TONB_H_
#define _TONB_H_ 1

//#include "tvector3.h"
#include "misc.h"

#define ONB_EPSILON 0.01f

class TONB
{
	public:
		TONB(){};
		TONB(const TVector3 u_,const TVector3 v_,const TVector3 w_);
		
		void initFromU( const TVector3 &u_);
		void initFromV( const TVector3 &v_);
		void initFromW( const TVector3 &w_);

		void set(const TVector3 u_,const TVector3 v_,const TVector3 w_);
		
		void initFromUV(const TVector3 &u_, const TVector3 &v_);
		void initFromVU(const TVector3 &v_, const TVector3 &u_);

		void initFromUW(const TVector3 &u_, const TVector3 &w_);
		void initFromWU(const TVector3 &w_, const TVector3 &u_);

		void initFromWV(const TVector3 &w_, const TVector3 &v_);
		void initFromVW(const TVector3 &v_, const TVector3 &w_);

		TVector3 getU() const;
		TVector3 getV() const;
		TVector3 getW() const;

		TVector3 u,v,w;
};

#endif // _TONB_H_

