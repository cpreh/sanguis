#ifndef SANGUIS_SERVER_BUFFS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_UNIQUE_PTR_HPP_INCLUDED

#include "buff_fwd.hpp"
#include <fcppt/unique_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

typedef fcppt::unique_ptr<
	buff
> unique_ptr;

}
}
}

#endif
