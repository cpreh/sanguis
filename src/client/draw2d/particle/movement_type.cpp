#include "movement_type.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <ostream>
#include <istream>

fcppt::io::ostream &
sanguis::client::draw2d::particle::operator<<(
	fcppt::io::ostream &s,
	movement_type::type const t)
{
	return s << static_cast<unsigned>(t);
}

fcppt::io::istream &
sanguis::client::draw2d::particle::operator>>(
	fcppt::io::istream &s,
	movement_type::type &t)
{
	unsigned i;
	s >> i;
	if (i >= movement_type::size)
		throw sge::exception(
			FCPPT_TEXT("invalid movement type"));
	t = static_cast<movement_type::type>(i);
	return s;
}
