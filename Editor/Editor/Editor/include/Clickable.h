////////////////////////////////////////////////////////////
//
// Clickable.h
//
// Uses Clickable.cpp
//
////////////////////////////////////////////////////////////
#ifndef CLICKABLE_H
#define CLICKABLE_H
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;



class Clickable
{
public :
	////////////////////////////////////////////////////////////
	/// \brief Overloaded Bool Function
	///
	/// Testes if the object has been clicked on
	///
	/// \param sfVmouseClick sf::Vector2f of where the mouse was clicked
	////////////////////////////////////////////////////////////
	bool m_bClicked(Vector2f sfVmouseClick);

	////////////////////////////////////////////////////////////
	/// \brief  m_sfVTopLeftPos sf::Vector2f where the top left of the button is
	////////////////////////////////////////////////////////////
	Vector2f m_sfVTopLeftPos;
	////////////////////////////////////////////////////////////
	/// \brief   m_sfVSize sf::Vector2f the size of the button
	////////////////////////////////////////////////////////////
	Vector2f m_sfVSize;

};
#endif

////////////////////////////////////////////////////////////
/// \class Clickable.h
///
/// Clickable.h is a blass class that will be used to test if an element has been clicked
///
/// Objects that can be clicked on should inherit from Clickable.h
///
/// It contains a public bool fuction that should be used to test is sometimes has been clicked on
///
/// Usage example:
/// \code
/// 
/// if(button01.m_bClicked(mousePosition)) window.open();
///
/// 
/// \endcode
///
////////////////////////////////////////////////////////////
