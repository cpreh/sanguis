#ifndef SANGUIS_MESSAGES_CONNECT_STATE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONNECT_STATE_FWD_HPP_INCLUDED

#include <sanguis/connect_state_fwd.hpp>
#include <sanguis/messages/enum_fwd.hpp>
#include <sanguis/messages/make_message_id_fwd.hpp>
#include <sanguis/messages/make_class_fwd.hpp>
#include <sanguis/messages/roles/connect_state.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/role_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
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
			sanguis::messages::make_message_id<
				sanguis::messages::types::message::connect_state
			>,
			majutsu::role<
				sanguis::messages::enum_<
					sanguis::connect_state
				>,
				sanguis::messages::roles::connect_state
			>
		>
	>
>
connect_state;

}
}

#endif
