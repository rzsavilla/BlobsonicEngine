/**
* @class	MyTimer
* @brief	Records time elapsed
* Used to track time in seconds that has elapsed
*/

#pragma once

class MyTimer {
private:
	float m_fStart;	//!< Start time
public:
	MyTimer();		//!< Default constructor

	void reset();			//!< Reset timer
	float getElapsed();		//!< Get elapsed time in seconds
};