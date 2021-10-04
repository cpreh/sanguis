#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_RANDOM_INCREASE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_RANDOM_INCREASE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>


namespace sanguis::server::weapons::modifiers
{

sanguis::server::space_unit
random_increase(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::server::entities::enemies::difficulty
);

}

#endif
