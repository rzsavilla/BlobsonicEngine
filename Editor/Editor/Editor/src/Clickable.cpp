#include "Clickable.h"

bool Clickable::m_bClicked(Vector2f sfVmouseClick)
{
	


	if (sfVmouseClick.x >= m_sfVTopLeftPos.x && sfVmouseClick.x <= m_sfVTopLeftPos.x + m_sfVSize.x)
	{
		
		if(sfVmouseClick.y >= m_sfVTopLeftPos.y && sfVmouseClick.y <= m_sfVTopLeftPos.y + m_sfVSize.y)
		{

			return true;
		}
	}

	return false;
}
