#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_FUNCTION_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_FUNCTION_HPP_INCLUDED

#include <sanguis/server/entities/property/change_event_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

typedef
void
change_function(
	sanguis::server::entities::property::change_event const &
);

}
}
}
}

#endif
