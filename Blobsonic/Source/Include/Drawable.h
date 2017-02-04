/**
* @class	Drawable
* @brief	Abstract class
* Allows an object to be drawn by render component
*/

#pragma once

class Drawable {
public:
	//! Virtual function called when object is drawn
	virtual void draw() = 0;
};