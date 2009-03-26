#ifndef SANGUIS_SERVER_ENTITIES_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_PTR_HPP_INCLUDED

#include "entity_fwd.hpp"
#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef sge::auto_ptr<entity> auto_ptr;

}
}
}

#endif
