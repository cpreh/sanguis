#ifndef SANGUIS_SERVER_ENTITIES_ENTITY_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENTITY_FWD_HPP_INCLUDED

#include <boost/ptr_container/ptr_list.hpp>
#include <memory>

namespace sanguis
{
namespace server
{
namespace entities
{

class entity;
typedef boost::ptr_list<entity> entity_container;
typedef std::auto_ptr<entity> entity_ptr;

}
}
}

#endif
