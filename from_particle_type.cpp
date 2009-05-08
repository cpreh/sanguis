#include "from_particle_type.hpp"
#include "exception.hpp"
#include <sge/text.hpp>

sge::string const sanguis::from_particle_type(particle_type::type const t)
{
	switch (t)
	{
		case particle_type::flare:
			return SGE_TEXT("flare");
		case particle_type::smoke:
			return SGE_TEXT("smoke");
		case particle_type::rubble:
			return SGE_TEXT("rubble");
		case particle_type::size:
			break;
	}
	throw exception(
		SGE_TEXT("invalid enumeration value for particle type"));
}
