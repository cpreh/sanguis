#ifndef SANGUIS_MESSAGES_MAKE_PLAYER_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_PLAYER_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/types/message.hpp>
#include <sanguis/messages/add_with_health.hpp>
#include <sanguis/messages/bind_entity_message.hpp>
#include <majutsu/composite.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

template<
	types::message::type Type
>
struct make_player_message
{
	typedef majutsu::composite<
		boost::mpl::vector2<
			typename messages::bind_entity_message<
				Type
			>::type,
			messages::add_with_health
		>
	> type;
};

}
}

#endif
