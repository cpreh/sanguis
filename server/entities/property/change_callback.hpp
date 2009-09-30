#ifndef SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROPERTY_CHANGE_CALLBACK_HPP_INCLUDED

#include "change_function.hpp"
#include <boost/function.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace property
{

typedef boost::function<
	change_function
> change_callback;

}
}
}
}

#endif
