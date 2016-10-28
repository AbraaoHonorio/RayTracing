#include "tonb.h"
#include <stdio.h>

//-----------------------------------------------------------------------------
TONB::TONB(const TVector3 u_,const TVector3 v_,const TVector3 w_)
{
	u = u_; 
	v = v_; 
	w = w_;
};

//-----------------------------------------------------------------------------
void TONB::initFromU( const TVector3 &u_)
{
	TVector3 n(1.0f,0.0f,0.0f);	
	TVector3 m(0.0f,1.0f,0.0f);	

	u = normal(u_);
	v = cross(u,n);
	
	if (sqr(v)<ONB_EPSILON)
		v = cross(u,m);
	
	w = cross(u,v);
};

//-----------------------------------------------------------------------------
void TONB::initFromV( const TVector3 &v_)
{
	TVector3 n(1.0f,0.0f,0.0f);	
	TVector3 m(0.0f,1.0f,0.0f);	

	v = normal(v_);
	u = cross(v,n);
	
	if (sqr(u)<ONB_EPSILON)
		u = cross(v,m);
 
	w = cross(u,v);
};

//-----------------------------------------------------------------------------
void TONB::initFromW( const TVector3 &w_)
{
	TVector3 n(1.0f,0.0f,0.0f);	
	TVector3 m(0.0f,1.0f,0.0f);	

	w = normal(w_);
	u = cross(w,n);
	
	if (sqr(u)<ONB_EPSILON)
		u = cross(w,m);
	
	v = cross(w,u);
};

//-----------------------------------------------------------------------------
void TONB::set(const TVector3 u_,const TVector3 v_,const TVector3 w_)
{
	u = u_; 
	v = v_; 
	w = w_;
};

//-----------------------------------------------------------------------------
void TONB::initFromUV(const TVector3 &u_, const TVector3 &v_)
{
	u = normal(u_);
	w = normal(cross(u_,v_));
	v = cross(w,u);
};

//-----------------------------------------------------------------------------
void TONB::initFromVU(const TVector3 &v_, const TVector3 &u_)
{
	v = normal(v_);
	w = normal(cross(u_,v_));
	u = cross(v,w);
};

//-----------------------------------------------------------------------------
void TONB::initFromUW(const TVector3 &u_, const TVector3 &w_)
{
	u = normal(u_);
	v = normal(cross(w_,u_));
	w = cross(u,v);
};

//-----------------------------------------------------------------------------
void TONB::initFromWU(const TVector3 &w_, const TVector3 &u_)
{
	w = normal(w_);
	v = normal(cross(w_,u_));
	u = cross(v,w);
};

//-----------------------------------------------------------------------------
void TONB::initFromWV(const TVector3 &v_, const TVector3 &w_)
{
	v = normal(v_);
	u = normal(cross(v_,w_));
	w = cross(u,v);
};

//-----------------------------------------------------------------------------
void TONB::initFromVW(const TVector3 &w_, const TVector3 &v_)
{
	w = normal(w_);
	u = normal(cross(v_,w_));
	v = cross(w,u);
};

//-----------------------------------------------------------------------------
TVector3 TONB::getU() const 
{ 
	return u; 
};

//-----------------------------------------------------------------------------
TVector3 TONB::getV() const 
{ 
	return v; 
};

//-----------------------------------------------------------------------------
TVector3 TONB::getW() const 
{ 
	return w; 
};

