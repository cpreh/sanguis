#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CONTAINER_HPP_INCLUDED

#include <sanguis/server/entities/enemies/modifiers/callback.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities::enemies::modifiers
{

using container = std::vector<sanguis::server::entities::enemies::modifiers::callback>;

}

#endif
