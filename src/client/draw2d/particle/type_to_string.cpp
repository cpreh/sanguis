#include <sanguis/client/draw2d/particle/type_to_string.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string const
sanguis::client::draw2d::particle::type_to_string(
	particle_type::type const _type
)
{
	switch(
		_type
	)
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

	FCPPT_ASSERT_UNREACHABLE
}
