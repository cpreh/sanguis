#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_CHANGE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_LINEAR_CHANGE_HPP_INCLUDED

#include <sanguis/server/entities/property/base_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

void
linear_change(
	sanguis::server::entities::property::base &,
	sanguis::server::entities::property::value const &
);

}
}
}
}

#endif
