#include "pickup_name.hpp"
#include <sge/text.hpp>
#include <sge/exception.hpp>

sge::string const
sanguis::load::pickup_name(
	pickup_type::type const ptype)
{
	switch(ptype) {
	case pickup_type::health:
		return sge::string(
			SGE_TEXT("pickup_hp"));
	default:
		throw sge::exception(
			SGE_TEXT("load::pickup_name: missing loading code!"));
	}
}
