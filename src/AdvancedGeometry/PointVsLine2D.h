// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsLine2D_H__
#define __AdvancedGeometry_PointVsLine2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D NearestPointOnLine2D( const Vector2D& p, const Vector2D& a, const Vector2D& b ) {
	Vector2D ab = b - a;
	Vector2D pa = a - p;
	
	Vector2D abNormal = ab;
	Real Width = abNormal.NormalizeRet();
	
	Real pdLength = pa * abNormal.Tangent();
	
	Vector2D d = p - (abNormal.Tangent() * pdLength);
	
	Vector2D ad = d - a;
	
	Real Offset = ad * abNormal;
	
	if ( Offset < Real::Zero ) {
		return a;
	}
	else if ( Offset > Width ) {
		return b;
	}
	else {
		return a + (abNormal * Offset);
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsLine2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
