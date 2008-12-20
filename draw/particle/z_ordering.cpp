#include "z_ordering.hpp"
#include <sge/text.hpp>
#include <sge/exception.hpp>

sanguis::draw::z_ordering::type
sanguis::draw::particle::z_ordering(
	particle_type::type const p)
{
	switch (p) {
	case particle_type::flare:
		return draw::z_ordering::flare;
	case particle_type::smoke:
		return draw::z_ordering::smoke;
	case particle_type::rubble:
		return draw::z_ordering::rubble;
	default:
		throw sge::exception(
			SGE_TEXT("invalid particle type!"));
	}
}
