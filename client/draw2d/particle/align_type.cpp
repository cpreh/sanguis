#include "align_type.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <ostream>
#include <istream>

fcppt::io::ostream &
sanguis::client::draw2d::particle::operator<<(
	fcppt::io::ostream &s,
	align_type::type const t)
{
	return s << static_cast<unsigned>(t);
}

fcppt::io::istream &
sanguis::client::draw2d::particle::operator>>(
	fcppt::io::istream &s,
	align_type::type &t)
{
	unsigned i;
	s >> i;
	if (i >= align_type::size)
		throw sge::exception(
			FCPPT_TEXT("invalid alignment type"));
	t = static_cast<align_type::type>(i);
	return s;
}
