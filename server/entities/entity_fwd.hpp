#ifndef SANGUIS_SERVER_ENTITIES_ENTITY_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENTITY_FWD_HPP_INCLUDED

#include <sge/auto_ptr.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class entity;
class entity_with_weapon;
typedef boost::ptr_list<entity> container;
typedef sge::auto_ptr<entity> auto_ptr;

}
}
}

#endif
