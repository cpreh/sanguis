#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_ACTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_ACTOR_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/add_elements_base_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_auras_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_buffs_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_health_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_weapon_fwd.hpp>
#include <sanguis/messages/server/parts/speed_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
boost::mpl::vector6<
	sanguis::messages::server::parts::add_elements_base,
	sanguis::messages::server::parts::speed,
	sanguis::messages::server::parts::add_with_health,
	sanguis::messages::server::parts::add_with_weapon,
	sanguis::messages::server::parts::add_with_auras,
	sanguis::messages::server::parts::add_with_buffs
>
add_actor;

}
}
}
}

#endif
