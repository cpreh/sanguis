#ifndef SANGUIS_MESSAGES_SERVER_RELOAD_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_RELOAD_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/duration_fwd.hpp>
#include <sanguis/messages/adapted_types/is_primary_weapon_fwd.hpp>
#include <sanguis/messages/roles/is_primary_weapon.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/server/types/make_message_id_fwd.hpp>
#include <sanguis/messages/server/types/message.hpp>
#include <alda/message/make_class_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

typedef
alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector3<
			sanguis::messages::server::types::make_message_id<
				sanguis::messages::server::types::message::reload
			>,
			majutsu::role<
				sanguis::messages::adapted_types::is_primary_weapon,
				sanguis::messages::roles::is_primary_weapon
			>,
			majutsu::role<
				sanguis::messages::adapted_types::duration,
				sanguis::messages::roles::reload_time
			>
		>
	>
>
reload;

}
}
}

#endif
