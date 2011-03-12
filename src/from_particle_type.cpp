#include "from_particle_type.hpp"
#include "exception.hpp"
#include <fcppt/text.hpp>

fcppt::string const sanguis::from_particle_type(particle_type::type const t)
{
	switch (t)
	{
		case particle_type::flare:
			return FCPPT_TEXT("flare");
		case particle_type::smoke:
			return FCPPT_TEXT("smoke");
		case particle_type::rubble:
			return FCPPT_TEXT("rubble");
		case particle_type::size:
			break;
	}
	throw exception(
		FCPPT_TEXT("invalid enumeration value for particle type"));
}
