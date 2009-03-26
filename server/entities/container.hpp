#ifndef SANGUIS_SERVER_ENTITIES_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_CONTAINER_HPP_INCLUDED

#include "entity_fwd.hpp"
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef boost::ptr_list<entity> container;

}
}
}

#endif
