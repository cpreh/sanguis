#ifndef SANGUIS_MESSAGES_BIND_ENTITY_MESSAGE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_BIND_ENTITY_MESSAGE_FWD_HPP_INCLUDED

#include <sanguis/messages/entity_message_fwd.hpp>
#include <sanguis/messages/make_message_id_fwd.hpp>
#include <sanguis/messages/types/message_fwd.hpp>
#include <majutsu/bind_fwd.hpp>
#include <majutsu/placeholder_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

template<
	sanguis::messages::types::message Msg
>
using bind_entity_message
=
majutsu::bind<
	sanguis::messages::entity_message,
	boost::mpl::vector2<
		sanguis::messages::make_message_id<
			Msg
		>,
		majutsu::placeholder
	>
>;

}
}

#endif
