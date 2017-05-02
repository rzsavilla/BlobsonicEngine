#include "Hoverable.h"

bool Hoverable::m_bHovering(Vector2f sfVmouseClick)
{
	if (sfVmouseClick.x >= m_sfVTopLeftPosHoverable.x && sfVmouseClick.x <= m_sfVTopLeftPosHoverable.x + m_sfVSizeHoverable.x)
	{
		if (sfVmouseClick.y >= m_sfVTopLeftPosHoverable.y && sfVmouseClick.y <= m_sfVTopLeftPosHoverable.y + m_sfVSizeHoverable.y)
		{
			return true;
		}
	}

	return false;
}