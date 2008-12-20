#include "movement_type.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <ostream>
#include <istream>

sge::ostream &
sanguis::draw::particle::operator<<(
	sge::ostream &s,
	movement_type::type const t)
{
	return s << static_cast<unsigned>(t);
}

sge::istream &
sanguis::draw::particle::operator>>(
	sge::istream &s,
	movement_type::type &t)
{
	unsigned i;
	s >> i;
	if (i >= movement_type::size)
		throw sge::exception(
			SGE_TEXT("invalid movement type"));
	t = static_cast<movement_type::type>(i);
	return s;
}
