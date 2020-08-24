#include "Research_Institute.h"

// copy c'tor
Research_Institute::Research_Institute(const Research_Institute& other)
{
	*this = other;
}
const Research_Institute& Research_Institute::operator=(const Research_Institute& i)
{
	if (this != &i)
	{
		AllResearchers = i.AllResearchers;
	}
	return *this;
}