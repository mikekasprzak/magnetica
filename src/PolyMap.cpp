// - ------------------------------------------------------------------------------------------ - //
#include <iostream>

#include "PolyMap.h"
#include "WhitespaceTokenizer.h"

using namespace std;
// - ------------------------------------------------------------------------------------------ - //
// TODO: Create a global array of Binary terms and codes, for binary generation. //
// - ------------------------------------------------------------------------------------------ - //
void cPolyMap::Load( const char* FileName ) {
	// A tokenizer for our file loader //
	cWhitespaceTokenizer File( FileName );
	
	// Tracked offset variable, if we choose to use the displacement command "Offset" //
	Vector3D Offset;
	
	// An enumeration for tracking the current creation mode, for keyword reuse //
	enum {
		ElementMode = 1,
		LinkMode = 2
	};
	size_t CreateMode = ElementMode;

	// For every line of the file, use the first token as the instruction to populate my data //
	do {
		// ----- Create Commands ------------------------------------------------------- //
		if ( File.IsStringToken( "Node" ) ) {
			CreateMode = ElementMode;
			File.NextToken();
			Element.push_back( cPolyMapElement( PME_NODE ) );

			Element.back().Center.x = File.StepFloatToken() + Offset.x;
			Element.back().Center.y = File.StepFloatToken() + Offset.y;
			Element.back().Center.z = File.StepFloatToken() + Offset.z;
		}
		else if ( File.IsStringToken( "Sphere" ) ) {
			CreateMode = ElementMode;
			File.NextToken();
			Element.push_back( cPolyMapElement( PME_SPHERE ) );

			Element.back().Center.x = File.StepFloatToken() + Offset.x;
			Element.back().Center.y = File.StepFloatToken() + Offset.y;
			Element.back().Center.z = File.StepFloatToken() + Offset.z;
		}
		else if ( File.IsStringToken( "Rect" ) ) {
			CreateMode = ElementMode;
			File.NextToken();
			Element.push_back( cPolyMapElement( PME_RECT ) );

			Element.back().Center.x = File.StepFloatToken() + Offset.x;
			Element.back().Center.y = File.StepFloatToken() + Offset.y;
			Element.back().Center.z = File.StepFloatToken() + Offset.z;
		}
		else if ( File.IsStringToken( "Poly" ) ) {
			CreateMode = ElementMode;
			File.NextToken();
			Element.push_back( cPolyMapElement( PME_POLY ) );

			Element.back().Center.x = File.StepFloatToken() + Offset.x;
			Element.back().Center.y = File.StepFloatToken() + Offset.y;
			Element.back().Center.z = File.StepFloatToken() + Offset.z;
		}
		else if ( File.IsStringToken( "Curve" ) ) {
			CreateMode = ElementMode;
			File.NextToken();
			Element.push_back( cPolyMapElement( PME_CURVE ) );

			Element.back().Center.x = File.StepFloatToken() + Offset.x;
			Element.back().Center.y = File.StepFloatToken() + Offset.y;
			Element.back().Center.z = File.StepFloatToken() + Offset.z;
		}
		else if ( File.IsStringToken( "Bone" ) ) {
			CreateMode = ElementMode;
			File.NextToken();
			Element.push_back( cPolyMapElement( PME_BONE ) );

			Element.back().Center.x = File.StepFloatToken() + Offset.x;
			Element.back().Center.y = File.StepFloatToken() + Offset.y;
			Element.back().Center.z = File.StepFloatToken() + Offset.z;
		}
		
		else if ( File.IsStringToken( "Link" ) ) {
			CreateMode = LinkMode;
			File.NextToken();
			Link.push_back( cPolyMapLink( 0 ) );

			Link.back().a = File.StepIntegerToken();
			Link.back().b = File.StepIntegerToken();
		}

		else if ( File.IsStringToken( "Key" ) ) {
			File.NextToken();
			
			string KeyName = File.StepStringToken();	
			Key[ KeyName ] = File.StepStringToken();
		}
		
		
		// ----- Modifier Commands (Changes Settings, Types, and Loader variables) ----- //
		else if ( File.IsStringToken( "Offset" ) ) {
			File.NextToken();
			
			Offset.x = File.StepFloatToken();
			Offset.y = File.StepFloatToken();
			Offset.z = File.StepFloatToken();
		}
		else if ( File.IsStringToken( "Center" ) ) {
			File.NextToken();
			
			Element.back().Center.x = File.StepFloatToken() + Offset.x;
			Element.back().Center.y = File.StepFloatToken() + Offset.y;
			Element.back().Center.z = File.StepFloatToken() + Offset.z;
		}
		else if ( File.IsStringToken( "Type" ) ) {
			File.NextToken();
			
			// Depending on the creation mode, set the info of the appropriate part //
			if ( CreateMode == ElementMode )
				Element.back().Type = File.StepIntegerToken();
			else if ( CreateMode == LinkMode )
				Link.back().Type = File.StepIntegerToken();
		}
		else if ( File.IsStringToken( "Id" ) ) {
			File.NextToken();
			
			Element.back().Id = File.StepIntegerToken();
		}
		else if ( File.IsStringToken( "Info" ) ) {
			File.NextToken();
			
			// Depending on the creation mode, set the info of the appropriate part //
			if ( CreateMode == ElementMode )
				Element.back().Info = File.StepIntegerToken();
			else if ( CreateMode == LinkMode )
				Link.back().Info = File.StepIntegerToken();
		}
		else if ( File.IsStringToken( "Pair" ) ) {
			File.NextToken();
			
			Link.back().a = File.StepIntegerToken();
			Link.back().b = File.StepIntegerToken();
		}
		
		
		// ----- Populating Commands (Adds elements to Vertex and Data) ----------------- //
		else if ( File.IsStringToken( "Vertex" ) ) {
			File.NextToken();
			
			float vx = File.StepFloatToken() + Offset.x;
			float vy = File.StepFloatToken() + Offset.y;
			float vz = File.StepFloatToken() + Offset.z;
			
			Element.back().Vertex.push_back( Vector3D( vx, vy, vz ) );
		}
		else if ( File.IsStringToken( "Radius" ) ) {
			File.NextToken();
			
			cPolyMapElement::PMEData MyData;
			MyData.f = File.StepFloatToken();
			
			Element.back().Data.push_back( MyData );
		}

	} while ( File.NextLine() );
}
// - ------------------------------------------------------------------------------------------ - //
void cPolyMap::Save( const char* FileName ) const {
	// A tokenizer for our file loader //
	cWhitespaceTokenizer File;

	// Write Header //
	File.Write() << "// Generated by cPolyMap - Mike Kasprzak (2008) //" << endl;
	File.Write() << endl;
	
	// ----- Write Elements ------------------------------------------------------------- //
	for ( size_t idx = 0; idx < Element.size(); idx++ ) {
		// Depending on the type, write different commands //
		if ( Element[idx].Type == PME_NODE ) {
			File.Write() << "Node ";
		}
		else if ( Element[idx].Type == PME_SPHERE ) {
			File.Write() << "Sphere ";
		}
		else if ( Element[idx].Type == PME_RECT ) {
			File.Write() << "Rect ";
		}
		else if ( Element[idx].Type == PME_POLY ) {
			File.Write() << "Poly ";
		}
		else if ( Element[idx].Type == PME_CURVE ) {
			File.Write() << "Curve ";
		}
		else if ( Element[idx].Type == PME_BONE ) {
			File.Write() << "Bone ";
		}
		
		// Append the center position //
		File.Write() << Element[idx].Center.x << " ";
		File.Write() << Element[idx].Center.y << " ";
		File.Write() << Element[idx].Center.z << endl;

		// If Id is not zero, write it //
		if ( Element[idx].Id != 0 ) {
			File.Write() << "Id " << Element[idx].Id << endl;
		}

		// If Info is not zero, write it //
		if ( Element[idx].Info != 0 ) {
			File.Write() << "Info " << Element[idx].Info << endl;
		}
		
		// Write Vertices //
		for ( size_t idx2 = 0; idx2 < Element[idx].Vertex.size(); idx2++ ) {
			File.Write() << "Vertex ";
			File.Write() << Element[idx].Vertex[idx2].x << " ";
			File.Write() << Element[idx].Vertex[idx2].y << " ";
			File.Write() << Element[idx].Vertex[idx2].z << endl;
		}
		
		// Write Data //
		if ( Element[idx].Type == PME_SPHERE ) {
			File.Write() << "Radius " << Element[idx].Data[0].f << endl;
		}
		else if ( Element[idx].Type == PME_BONE ) {
			for ( size_t idx2 = 0; idx2 < Element[idx].Data.size(); idx2++ ) {
				// TODO: Bone stuff
				//Element[idx].Data[idx2].i
			}
		}
	}

	// ----- Write Links ---------------------------------------------------------------- //
	for ( size_t idx = 0; idx < Link.size(); idx++ ) {
		// Write link including the a and b pairs //
		File.Write() << "Link " <<
			Link[idx].a << " " <<
			Link[idx].b << endl;
		
		// If Id is not zero, write it //
		if ( Link[idx].Type != 0 ) {
			File.Write() << "Id " << Link[idx].Type << endl;
		}

		// If Info is not zero, write it //
		if ( Link[idx].Info != 0 ) {
			File.Write() << "Info " << Link[idx].Info << endl;
		}
	}
	
	// ----- Write Keys ----------------------------------------------------------------- //
	for ( cKeyIterator it = Key.begin(); it != Key.end(); it++ ) {
		File.Write() << "Key " << it->first << " \"" << it->second << "\"" << endl;
	}


	// ----- Write the file ------------------------------------------------------------- //
	File.Save( FileName );
}
// - ------------------------------------------------------------------------------------------ - //
