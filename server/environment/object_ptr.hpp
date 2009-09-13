#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_PTR_HPP_INCLUDED

#include "object_fwd.hpp"
#include <sge/shared_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace environment
{

typedef sge::shared_ptr<
	object
> object_ptr;

}
}
}

#endif
