#ifndef SANGUIS_SERVER_ENTITIES_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef sge::auto_ptr<
	base
> auto_ptr;

}
}
}

#endif
