#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_CONTAINER_HPP_INCLUDED

#include <sanguis/server/entities/enemies/skills/factory/callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::server::entities::enemies::skills::factory
{

using
container
=
std::vector<
	sanguis::server::entities::enemies::skills::factory::callback
>;

}

#endif
