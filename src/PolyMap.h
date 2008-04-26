// - ------------------------------------------------------------------------------------------ - //
// Generic game geometry info file //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __PolyMap_H__
#define __PolyMap_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <map>
#include <string>

#include "Math/Vector/Vector3D.h"
// - ------------------------------------------------------------------------------------------ - //
// Enumerations for Element Type //
enum {
	PME_NODE = 1,
	PME_SPHERE,
	PME_RECT,
	PME_POLY,
	PME_CURVE,
	PME_BONE,
	
	PME_END
};
// - ------------------------------------------------------------------------------------------ - //
class cPolyMapElement {
public:
	// What type of element it is (Node, Sphere, Rectangle, Polygon, etc...)
	size_t Type;
	
	// Center position //
	Vector3D Center;
	
	// All vertices found in the element (Node - unused) //
	std::vector< Vector3D > Vertex;
	
	// A type for the arbitrary data section, Data //	
	union PMEData {
		float f;
		int i;
		unsigned int u;
		unsigned char b[4];
		char c[4];
		short s[2];
		unsigned short w[2];
	};
	
	// The arbitrary data section //
	std::vector< PMEData > Data;
	
	// The type of the type.  Is it a collision polygon, or a safe zone polygon? //
	size_t Id;
	
	// Additional information/subcategorization of the element (argument) //
	int Info;

public:
	cPolyMapElement() :
		Type( 0 ),
		Id( 0 ),
		Info( 0 )
	{
	}
	
	cPolyMapElement( const size_t _Type ) :
		Type( _Type ),
		Id( 0 ),
		Info( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cPolyMapLink {
public:
	// The type or classification of the Link.  Paths, Branches, Springs, etc. //
	size_t Type;
	
	// The associated elements //
	size_t a;
	size_t b;
	
	// Additional information of the Link (argument) //
	int Info;

public:
	cPolyMapLink() :
		Type( 0 ),
		Info( 0 )
	{
	}

	cPolyMapLink( const size_t _Type ) :
		Type( _Type ),
		Info( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cPolyMap {
public:
	// Array of Elements //
	std::vector< cPolyMapElement > Element;
	// Array of Links //
	std::vector< cPolyMapLink > Link;
	
	// Map of information keys //
	typedef std::map< const std::string, std::string > cPolyMapKey;
	typedef cPolyMapKey::const_iterator cKeyIterator;
	cPolyMapKey Key;
	
public:
	cPolyMap() {
	}
	
	cPolyMap( const char* FileName ) {
		Load( FileName );
	}
	
	void Load( const char* FileName );
	void Save( const char* FileName ) const;

public:
	// Helper functions for accessing the key as other types //
	inline const std::string GetStringKey( const std::string _Key ) {
		return Key[ _Key ];
	}
	inline const int GetIntegerKey( const std::string _Key ) {
		return atoi( Key[ _Key ].c_str() );
	}
	inline const float GetFloatKey( const std::string _Key ) {
		return atof( Key[ _Key ].c_str() );
	}	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PolyMap_H__ //
// - ------------------------------------------------------------------------------------------ - //
