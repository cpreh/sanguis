#ifndef SANGUIS_SERVER_BUFFS_AUTO_PTR_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_AUTO_PTR_HPP_INCLUDED

#include <sge/auto_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

class buff;
typedef sge::auto_ptr<
	buff
> auto_ptr;

}
}
}

#endif
