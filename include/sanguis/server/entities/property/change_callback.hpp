#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/property/change_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

typedef std::function<
	sanguis::server::entities::property::change_function
> change_callback;

}
}
}
}

#endif
