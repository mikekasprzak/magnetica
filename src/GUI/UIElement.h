// - ------------------------------------------------------------------------------------------ - //
// Base Class of the UI Element Framework //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GUI_UIElement_H__
#define __GUI_UIElement_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector/Vector2D.h>
// - ------------------------------------------------------------------------------------------ - //
class cUIElement {
public:
	// Pos -- The "notable" home point of an element //
	// If physics or 3D are introduced in to the GUI system, this simply becomes a home //
	// Reference point for new instances. Smart code behind the system can use this point for //
	// knowing where to center, to rest, or similar such uses. //
	Vector2D Pos;
	
	// GroupId -- Basic hierarchical grouping implementation //
	// Through accessor functions, like in current system, perform group actions on all //
	// members of the group, such as setting visibility //
	int GroupId;
	
	// Value -- Basic incremental numerical contents //
	// Checkboxes or toggle menu items have values of 0 or 1.  Multi select would have 0 or //
	// more to choose from.  Value should be controlled via accessor functions that through //
	// virtual function correctly clip it to it's range.  If unused, then it's not important. //
	int Value;
	
	// IsVisible -- Flag for noting individual element visibilty //
	// Parent objects will determine visibilty for all it's children, but this is control on //
	// an individual object level.  Usually combined with the GroupId concept. //
	bool IsVisible;
	
	
	// Other (Not sure if these are appropriate) -------------------------------------------- //
	
	// Selection Orderings.  Important, but there are 2 distinct ways it can be approached //
	
	// TabStop -- While not technically "tab", it's the order to "Tab" to //
	// The positive numeric ordering to follow when going forward/back.  If negative (-1) //
	// then ignore this object in flow orderings. //
	int TabStop;
	
	// Tab stop might be too archaic of a concept, so the alternative is to use positional //
	// information, and simply note if it's on the list of things or not, given the desired //
	// selection direction. //
	
	// IsSelectable -- Is it selectable, hence, if its the nearest element below me, pushing //
	// down goes to it. It's either this, or TabStop.  //
	bool IsSelectable;
	
	// Technically, both implementations are fine.  Generally speaking, a cohesive menu that //
	// flows top to bottom is more natural, and only to the left/right on accept/cancel //
	// actions. //
	
	// The third option is linear order.  Essentially, selecting objects by the order in the //
	// Gui info file.  There's honestly no real advantage to this, short of 2-3 lines easier //
	// of an implementation.  Selectable + Position disregards and can order nicely.  TabStop //
	// alone can do the order just fine, but tabstopping is more effort than Selectable + //
	// Position because the tabstop needs to be set/identified.  It's very uncommon to want //
	// to select things out of a cohesive top to bottom order (1, 3, 2).  A reasonable //
	// restriction. //
	
	// -------------------------------------------------------------------------------------- //
	
	// Parental relationship. //
	// There are many advantages to knowing who your parent is, specifically, the ability to //
	// step backwards in a heiarchy to learn about your neighbours/parents parent/etc. //
	
	// This is essential to a game engine, but optional for a Gui system.  However, for the //
	// added flexibility for custom code, it's probably worth doing. //
	
	// This leads to functions such as "ScreenPos" for an objects real screen position.  It's //
	// implemented by stepping up the tree to the root (no parent) and suming the positions //
	// found in every element.  Not a bad function to have, though drawing can work without //
	// it since it's the root that will request the draw operation, and traveling down the //
	// tree is a natual feature of a heiarchy. //
	
	// The "root" should be a member of the manager class.  There's no reason for it to be a //
	// dynamic member like every element.  It can be the base type as well. //
	
	// Parent -- Whom lives/goes before me in the heiarchy //
	cUIElement* Parent;
	
	// -------------------------------------------------------------------------------------- //
	
public:
	// General implementation of a work function.  Follows internal game framerate. //
	virtual void Step()
	{
	}
	// General implementation of drawing.  Takes a positional offset, so to create a hierarchy//
	// where the parent can say where I draw relative to. //
	virtual void Draw( const Vector2D& Offset = Vector2D::Zero )
	{
	}		
}; // class cUIElement //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GUI_UIElement_H__ //
// - ------------------------------------------------------------------------------------------ - //
