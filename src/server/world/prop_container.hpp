#ifndef SANGUIS_SERVER_WORLD_PROP_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_PROP_CONTAINER_HPP_INCLUDED

#include "prop_fwd.hpp"
#include <boost/ptr_container/ptr_vector.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

typedef boost::ptr_vector<
	prop
> prop_container;

}
}
}

#endif
