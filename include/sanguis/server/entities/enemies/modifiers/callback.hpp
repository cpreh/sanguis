#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>


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

// TODO: These might need to be classes in order to compare and bind
typedef
sanguis::server::entities::enemies::attribute
(*callback)(
	sanguis::server::entities::enemies::parameters &
);

}
}
}
}
}

#endif
