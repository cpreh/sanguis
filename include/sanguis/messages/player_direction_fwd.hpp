#ifndef SANGUIS_MESSAGES_PLAYER_DIRECTION_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_PLAYER_DIRECTION_FWD_HPP_INCLUDED

#include <sanguis/messages/bind_player_message_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/vector2_fwd.hpp>
#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/roles/direction.hpp>
#include <majutsu/composite_fwd.hpp>
#include <majutsu/role_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

typedef
sanguis::messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			sanguis::messages::bind_player_message<
				sanguis::messages::types::message::player_direction
			>,
			majutsu::role<
				sanguis::messages::vector2,
				sanguis::messages::roles::direction
			>
		>
	>
>
player_direction;

}
}

#endif
