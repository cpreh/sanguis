#ifndef SANGUIS_SERVER_WEAPONS_SPREAD_RADIUS_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SPREAD_RADIUS_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::server::space_unit,
	spread_radius
);

}
}
}

#endif
