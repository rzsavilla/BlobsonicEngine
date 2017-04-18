#pragma once

class Destroyable {
private:
	bool m_bDestroyed;
public:
	Destroyable();			//!< Default constructor
	void destroy();			//!< Set boolean m_bDestroyed to true
	bool isDestroyed();		//!< Checks if destroyed is true
};