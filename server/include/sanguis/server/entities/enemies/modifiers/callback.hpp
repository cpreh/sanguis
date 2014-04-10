#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace modifiers
{

using
callback
=
sanguis::server::entities::enemies::attribute
(*)(
	sanguis::server::entities::enemies::parameters &,
	sanguis::server::entities::enemies::modifiers::parameters const &
);

}
}
}
}
}

#endif
