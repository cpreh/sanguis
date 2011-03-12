#ifndef SANGUIS_SERVER_ENVIRONMENT_OBJECT_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENVIRONMENT_OBJECT_PTR_HPP_INCLUDED

#include "object_fwd.hpp"
#include <fcppt/shared_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace environment
{

typedef fcppt::shared_ptr<
	object
> object_ptr;

}
}
}

#endif
