/*
*	@class LuaEntity
*	@brief Gives objects a string name
*	@author Rozen Savilla
*	Simple function stores a name for derived classes allowing them 
*	to easily set and get a string name.
*	Names are not unique
*/

#pragma once

#include "stdafx.h"

class Name {
private:
	std::string m_sName;
public:
	Name();	//!< Default constructor

	void setName(const std::string& newName);	//!< Set the value of name string
	std::string getName();						//!< Get the value of name string
};