#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_FREEZING_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_FREEZING_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis::server::entities::enemies::modifiers
{

sanguis::server::entities::enemies::attribute
freezing(
	fcppt::reference<
		sanguis::server::entities::enemies::parameters
	>,
	sanguis::server::entities::enemies::modifiers::parameters const &
);

}

#endif
