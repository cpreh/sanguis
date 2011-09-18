#ifndef SANGUIS_MESSAGES_BIND_ENTITY_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_BIND_ENTITY_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/entity_message.hpp>
#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/types/message.hpp>
#include <majutsu/bind.hpp>
#include <majutsu/placeholder.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace messages
{

template<
	types::message::type Msg
>
struct bind_entity_message
{
	typedef majutsu::bind<
		messages::entity_message,
		boost::mpl::vector2<
			typename messages::make_message_id<
				Msg
			>::type,
			majutsu::placeholder
		>
	> type;
};

}
}

#endif
