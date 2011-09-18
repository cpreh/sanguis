#ifndef SANGUIS_MESSAGES_CONNECT_STATE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CONNECT_STATE_HPP_INCLUDED

#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/make_class.hpp>
#include <sanguis/messages/enum.hpp>
#include <sanguis/messages/roles/connect_state.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/role.hpp>
#include <majutsu/composite.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

typedef messages::make_class<
	majutsu::composite<
		boost::mpl::vector2<
			messages::make_message_id<
				types::message::connect_state
			>::type,
			majutsu::role<
				messages::enum_,
				roles::connect_state
			>
		>
	>
>::type connect_state;

}
}

#endif
