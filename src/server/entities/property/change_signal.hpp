#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_SIGNAL_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_SIGNAL_HPP_INCLUDED

#include "change_function.hpp"
#include <fcppt/signal/object.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

typedef fcppt::signal::object<
	change_function
> change_signal;

}
}
}
}

#endif
