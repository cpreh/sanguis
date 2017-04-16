#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_BASE_HOOK_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_BASE_HOOK_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{
namespace simple
{

typedef
boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
>
body_base_hook;

}
}
}
}
}

#endif
