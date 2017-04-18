#include "stdafx.h"
#include "Destroyable.h"

Destroyable::Destroyable()
{
	m_bDestroyed = false;
}

void Destroyable::destroy()
{
	m_bDestroyed = true;
}

bool Destroyable::isDestroyed()
{
	return m_bDestroyed;
}
