#ifndef SANGUIS_MESSAGES_MAKE_PLAYER_MESSAGE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_PLAYER_MESSAGE_FWD_HPP_INCLUDED

#include <sanguis/messages/add_with_auras_fwd.hpp>
#include <sanguis/messages/bind_entity_message_fwd.hpp>
#include <sanguis/messages/types/message_fwd.hpp>
#include <majutsu/composite_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{

template<
	sanguis::messages::types::message Type
>
using make_player_message
=
majutsu::composite<
	boost::mpl::vector2<
		sanguis::messages::bind_entity_message<
			Type
		>,
		sanguis::messages::add_with_auras
	>
>;

}
}

#endif
