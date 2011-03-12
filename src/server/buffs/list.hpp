#ifndef SANGUIS_SERVER_BUFFS_LIST_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_LIST_HPP_INCLUDED

#include "buff_fwd.hpp"
#include <boost/intrusive/list.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

typedef boost::intrusive::list<
	buff,
	boost::intrusive::constant_time_size<
		false
	>
> list;

}
}
}

#endif
