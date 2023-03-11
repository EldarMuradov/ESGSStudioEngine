#include "Counter.h"

int Counter::m_count = 0;

int Counter::getCount()
{
	m_count++;
	return m_count;
}
