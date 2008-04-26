// - ------------------------------------------------------------------------------------------ - //
#ifndef __AdvancedGeometry_PointVsChain2D_H__
#define __AdvancedGeometry_PointVsChain2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D NearestPointOnChain2D( const Vector2D& Pos, const Vector2D* VsPoint, const size_t VsCount ) {
	Vector2D Point;
	Real DistanceSquared;
	
	if ( VsCount >= 1 ) {
		Point = NearestPointOnLine2D( Pos, VsPoint[ VsCount - 1 ], VsPoint[ 0 ] );
		DistanceSquared = (Point - Pos).MagnitudeSquared();
		
		for ( size_t idx = 0; idx < VsCount - 1; idx++ ) {
			Vector2D NewPoint = NearestPointOnLine2D( Pos, VsPoint[ idx ], VsPoint[ idx + 1 ] );
			Real NewDistanceSquared = (NewPoint - Pos).MagnitudeSquared();
			
			if ( DistanceSquared > NewDistanceSquared ) {
				Point = NewPoint;
				DistanceSquared = NewDistanceSquared;
			}
		}
	}
	
	return Point;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __AdvancedGeometry_PointVsChain2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
