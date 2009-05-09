#ifndef SANGUIS_SERVER_ENTITIES_LINK_CONTAINER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_LINK_CONTAINER_HPP_INCLUDED

#include "auto_weak_link_fwd.hpp"
#include <boost/intrusive/list.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef boost::intrusive::list<
	auto_weak_link,
	boost::intrusive::constant_time_size<
		false
	>
> link_container;

}
}
}

#endif
