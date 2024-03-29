#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FINALIZE_SPECIAL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FINALIZE_SPECIAL_PARAMETERS_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/skills/factory/container.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sanguis::server::entities::enemies
{

sanguis::server::entities::enemies::parameters &finalize_special_parameters(
    fcppt::reference<sanguis::server::entities::enemies::parameters>,
    sanguis::server::entities::enemies::attribute_container const &,
    sanguis::server::entities::enemies::skills::factory::container const &);

}

#endif
