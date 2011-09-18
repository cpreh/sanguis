#include <sanguis/client/draw2d/particle/z_ordering.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <fcppt/assert/unreachable.hpp>

sanguis::client::draw2d::z_ordering::type
sanguis::client::draw2d::particle::z_ordering(
	particle_type::type const _type
)
{
	switch(
		_type
	)
	{
	case particle_type::flare:
		return draw2d::z_ordering::flare;
	case particle_type::smoke:
		return draw2d::z_ordering::smoke;
	case particle_type::rubble:
		return draw2d::z_ordering::rubble;
	case particle_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE
}
