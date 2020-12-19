#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_SKILLS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_SKILLS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
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

sanguis::server::entities::enemies::skills::factory::container
make_skills(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::server::random::amount
);

}
}
}
}
}

#endif
