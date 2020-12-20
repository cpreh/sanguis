#ifndef SANGUIS_SERVER_WEAPONS_RANDOM_ANGLE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_RANDOM_ANGLE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/weapons/accuracy.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

sanguis::server::angle
random_angle(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::server::weapons::accuracy,
	sanguis::server::angle
);

}
}
}

#endif
