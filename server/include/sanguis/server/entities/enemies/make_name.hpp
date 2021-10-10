#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MAKE_NAME_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MAKE_NAME_HPP_INCLUDED

#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/skills/container.hpp>
#include <fcppt/string.hpp>

namespace sanguis::server::entities::enemies
{

fcppt::string make_name(
    sanguis::server::entities::enemies::attribute_container const &,
    sanguis::server::entities::enemies::skills::container const &,
    sanguis::creator::enemy_type);

}

#endif
