#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_SKILLS_FACTORY_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/enemies/skills/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/skills/factory/parameters_fwd.hpp>

namespace sanguis::server::entities::enemies::skills::factory
{

using callback = sanguis::server::entities::enemies::skills::unique_ptr (*)(
    sanguis::server::entities::enemies::skills::factory::parameters const &);

}

#endif
