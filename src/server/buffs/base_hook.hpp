#ifndef SANGUIS_SERVER_BUFFS_BASE_HOOK_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BASE_HOOK_HPP_INCLUDED

#include <boost/intrusive/list_hook.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

typedef boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
> base_hook;

}
}
}

#endif
