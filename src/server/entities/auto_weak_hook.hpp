#ifndef SANGUIS_SERVER_ENTITIES_AUTO_WEAK_HOOK_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_AUTO_WEAK_HOOK_HPP_INCLUDED

#include <boost/intrusive/list_hook.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
> auto_weak_hook;

}
}
}

#endif
