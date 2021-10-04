#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_SCATTER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_SCATTER_HPP_INCLUDED

#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters_fwd.hpp>


namespace sanguis::server::entities::enemies::skills::factory
{

sanguis::server::entities::enemies::skills::unique_ptr
scatter(
	sanguis::server::entities::enemies::skills::factory::parameters const &
);

}

#endif
