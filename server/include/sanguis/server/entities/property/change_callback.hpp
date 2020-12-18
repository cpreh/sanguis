#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED

#include <sanguis/server/entities/property/change_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

using
change_callback
=
fcppt::function<
	sanguis::server::entities::property::change_function
>;

}
}
}
}

#endif
