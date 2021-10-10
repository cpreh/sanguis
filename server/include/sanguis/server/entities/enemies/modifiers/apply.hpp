#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_APPLY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_APPLY_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/attribute_container.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sanguis::server::entities::enemies::modifiers
{

sanguis::server::entities::enemies::attribute_container apply(
    sanguis::random_generator &, // NOLINT(google-runtime-references)
    fcppt::reference<sanguis::server::entities::enemies::parameters>,
    sanguis::server::entities::enemies::modifiers::container const &);

}

#endif
