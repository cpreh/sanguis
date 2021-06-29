#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_ACTOR_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_ACTOR_FWD_HPP_INCLUDED

#include <sanguis/messages/server/parts/add_elements_base_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_auras_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_buffs_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_health_fwd.hpp>
#include <sanguis/messages/server/parts/add_with_weapon_fwd.hpp>
#include <sanguis/messages/server/parts/speed_fwd.hpp>
#include <fcppt/mpl/list/join.hpp>
#include <fcppt/mpl/list/object.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

using
add_actor
=
fcppt::mpl::list::join<
	fcppt::mpl::list::object<
		sanguis::messages::server::parts::add_elements_base,
		fcppt::mpl::list::object<
			sanguis::messages::server::parts::speed
		>,
		sanguis::messages::server::parts::add_with_health,
		sanguis::messages::server::parts::add_with_weapon,
		fcppt::mpl::list::object<
			sanguis::messages::server::parts::add_with_auras
		>,
		fcppt::mpl::list::object<
			sanguis::messages::server::parts::add_with_buffs
		>
	>
>;

}
}
}
}

#endif
