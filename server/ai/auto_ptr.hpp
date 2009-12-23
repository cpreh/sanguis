#ifndef SANGUIS_SERVER_AI_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_AI_AUTO_PTR_HPP_INCLUDED

#include "base_fwd.hpp"
#include <fcppt/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace ai
{

typedef fcppt::auto_ptr<
	base
> auto_ptr;

}
}
}

#endif
