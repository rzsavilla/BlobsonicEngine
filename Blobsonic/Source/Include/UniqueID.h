/*!
*	@class UniqueID
*	@author Rozen Savilla
*	@brief Simple unique identifier
*	Class is simply inherited by object which requires a unique ID,
*	UID should be called within the constructor of the derived class
*/

#pragma once

class UniqueID {
private:
	static int ms_iUIDCounter;	//!< Counter for generating ID's
	unsigned int m_uiUID;		//!< Set/Permanent Unique Identification
protected:
	/*! 
	*	Generates and sets this objects UID Call inside the constructor of derived class
	*/
	void setUID();				
public:
	int getUID();		//!< Returns UID
};