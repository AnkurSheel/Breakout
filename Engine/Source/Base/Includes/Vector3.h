// *****************************************************************************
//  Vector3   version:  1.0   Ankur Sheel  date: 2012/08/28
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Vector3_h__
#define Vector3_h__

namespace Base
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Encapsulates a 3D vector with X, Y and Z components .
	///
	///////////////////////////////////////////////////////////////////////////
	class cVector3
	{
	public:
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////
		cVector3();
		///////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] X The X component of the vector
		/// @param[in] Y The Y component of the vector
		/// @param[in] Z The Z component of the vector
		///
		///////////////////////////////////////////////////////////////////////
		cVector3(const float X, const float Y, const float Z);
		///////////////////////////////////////////////////////////////////////
		/// Returns true if the vector is 0.
		///
		/// @return True if the vector is 0
		///
		///////////////////////////////////////////////////////////////////////
		bool IsZero() const;	
		///////////////////////////////////////////////////////////////////////
		/// Returns the length of the vector.
		///
		/// @return Length of the vector
		///
		///////////////////////////////////////////////////////////////////////
		float Length() const;
		///////////////////////////////////////////////////////////////////////
		/// Returns the squared length of the vector.
		///
		/// @return Squared length of the vector 
		///
		///////////////////////////////////////////////////////////////////////
		float LengthSquared() const;
		///////////////////////////////////////////////////////////////////////
		/// Converts the Vector into a unit vector
		///
		///
		///////////////////////////////////////////////////////////////////////
		void Normalize();
		///////////////////////////////////////////////////////////////////////
		/// Calculates and returns the dot product.
		///
		/// @param[in] inVec The vector with which the dot product needs to be
		/// calculated
		/// @return The dot product between this vector and the one passed as
		/// a parameter
		///
		///////////////////////////////////////////////////////////////////////
		float Dot(const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////
		/// Calculate and returns a vector perpendicular to these vectors.
		///
		/// @param[in] inVec the vector with which the cross product needs to
		/// be calculated.
		/// @return the cross product between these 2 vectors.
		///
		///////////////////////////////////////////////////////////////////////
		cVector3 Cross( const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////
		/// Returns the distance between this vector and the one passed as a 
		/// parameter.
		///
		/// @param[in] inVec The vector with which the distance needs to 
		/// be calculated
		/// @return Euclidean distance 
		///
		///////////////////////////////////////////////////////////////////////
		float Distance(const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////
		/// Returns the squared distance between this vector and the one passed
		/// as a parameter
		///
		/// @param[in] inVec The vector with which the distance needs to be
		/// calculated.
		/// @return Squared euclidean distance 
		///////////////////////////////////////////////////////////////////////
		float DistanceSquared(const cVector3 & inVec) const;
		///////////////////////////////////////////////////////////////////////
		/// Sets the components to their absolute values.
		///
		/// 
		///////////////////////////////////////////////////////////////////////
		void AbsTo();
		///////////////////////////////////////////////////////////////////////
		/// Get the largest coordinate and return a signed, unit vector
		/// containing only that coordinate.
		///
		/// @return A signed, unit vector containing only the largest coordinate
		/// 
		///////////////////////////////////////////////////////////////////////
		cVector3 MajorAxis() const;
		///////////////////////////////////////////////////////////////////////
		/// Get the smallest coordinate and return a signed, unit vector
		/// containing only that coordinate.
		///
		/// @return A signed, unit vector containing only the smallest coordinate
		/// 
		///////////////////////////////////////////////////////////////////////
		cVector3 MinorAxis() const;
		///////////////////////////////////////////////////////////////////////
		/// Changes the sign of the components.
		///
		/// 
		///////////////////////////////////////////////////////////////////////
		void NegTo();
		///////////////////////////////////////////////////////////////////////
		/// Gets the reverse vector
		///
		/// @return Reverse of this vector
		/// 
		///////////////////////////////////////////////////////////////////////
		cVector3 GetReverse();

		const cVector3 & operator+=(const cVector3 & inVec);
		const cVector3 & operator-=(const cVector3 & inVec);
		const cVector3 & operator*=(const cVector3 & inVec);
		const cVector3 & operator*=(const float & fVal);
		const cVector3 & operator/=(const float & fVal);
		bool operator==(const cVector3 & inVec) const;
		bool operator!=(const cVector3 & inVec) const;
		float & operator[](const unsigned int i);
		const float operator[](const unsigned int i) const;

		static cVector3 Zero();
		static cVector3 Lerp(const cVector3 from, const cVector3 to, float alpha);

	public:
		float	x;	///< X component of Vector3
		float	y;	///< Y component of Vector3
		float	z;	///< Z component of Vector3
	};

inline cVector3 operator*(const cVector3 & inVec1, const float fVal);
inline cVector3 operator*(const float fVal, const cVector3 & inVec1);
inline cVector3 operator/(const cVector3 & inVec1, const float fVal);
inline cVector3 operator-(const cVector3 & inVec1, const cVector3 & inVec2);
inline cVector3 operator+(const cVector3 & inVec1, const cVector3 & inVec2);
inline cVector3 operator*(const cVector3 & inVec1, const cVector3 & inVec2);

#include "Vector3.inl"
}
#endif // Vector3_h__
