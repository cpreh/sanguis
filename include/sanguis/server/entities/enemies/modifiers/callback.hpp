#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_MODIFIERS_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/enemies/attribute_fwd.hpp>
#include <sanguis/server/entities/enemies/parameters_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


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

typedef
std::function<
	sanguis::server::entities::enemies::attribute (
		sanguis::server::entities::enemies::parameters &
	)
>
callback;

}
}
}
}
}

#endif
