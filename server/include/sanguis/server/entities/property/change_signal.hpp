#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_SIGNAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_SIGNAL_HPP_INCLUDED

#include <sanguis/server/entities/property/change_function.hpp>
#include <fcppt/signal/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

using
change_signal
=
fcppt::signal::object<
	sanguis::server::entities::property::change_function
>;

}
}
}
}

#endif
