#ifndef SANGUIS_MESSAGES_SERVER_LEVEL_UP_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_LEVEL_UP_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/exp_fwd.hpp>
#include <sanguis/messages/adapted_types/level_fwd.hpp>
#include <sanguis/messages/roles/exp_for_next_level.hpp>
#include <sanguis/messages/roles/level.hpp>
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
				sanguis::messages::server::types::message::level_up
			>,
			majutsu::role<
				sanguis::messages::adapted_types::level,
				sanguis::messages::roles::level
			>,
			majutsu::role<
				sanguis::messages::adapted_types::exp,
				sanguis::messages::roles::exp_for_next_level
			>
		>
	>
>
level_up;

}
}
}

#endif
