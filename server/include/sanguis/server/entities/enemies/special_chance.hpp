#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_CHANCE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SPECIAL_CHANCE_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::server::entities::enemies
{

FCPPT_DECLARE_STRONG_TYPEDEF(
	sanguis::server::space_unit,
	special_chance
);

}

#endif
