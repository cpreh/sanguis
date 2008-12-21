#include "align_type.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <ostream>
#include <istream>

sge::ostream &
sanguis::draw::particle::operator<<(
	sge::ostream &s,
	align_type::type const t)
{
	return s << static_cast<unsigned>(t);
}

std::istream &
sanguis::draw::particle::operator>>(
	sge::istream &s,
	align_type::type &t)
{
	unsigned i;
	s >> i;
	if (i >= align_type::size)
		throw sge::exception(
			SGE_TEXT("invalid alignment type"));
	t = static_cast<align_type::type>(i);
	return s;
}
