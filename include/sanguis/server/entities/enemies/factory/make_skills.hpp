#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_SKILLS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_SKILLS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <sanguis/server/random/amount.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace factory
{

sanguis::server::entities::enemies::skills::container
make_skills(
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	sanguis::server::random::amount,
	sanguis::server::entities::enemies::difficulty
);

}
}
}
}
}

#endif
