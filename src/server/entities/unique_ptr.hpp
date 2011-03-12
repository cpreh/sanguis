#ifndef SANGUIS_SERVER_ENTITIES_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_UNIQUE_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef fcppt::unique_ptr<
	base
> unique_ptr;

}
}
}

#endif
