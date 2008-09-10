#include "decoration_name.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::string const
sanguis::load::decoration_name(
	decoration_type::type const etype)
{
	switch(etype) {
	case decoration_type::barrel:
		return SGE_TEXT("decoration/barrel");
	case decoration_type::rock:
		return SGE_TEXT("decoration/rock");
	case decoration_type::crate:
		return SGE_TEXT("decoration/crate");
	default:
		throw sge::exception(
			SGE_TEXT("load::decoration_name: missing loading code!"));
	}
}
