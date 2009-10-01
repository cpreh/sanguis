#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED

#include "change_function.hpp"
#include <sge/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

typedef sge::function::object<
	change_function
> change_callback;

}
}
}
}

#endif
