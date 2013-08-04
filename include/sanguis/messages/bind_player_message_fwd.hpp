#ifndef SANGUIS_MESSAGES_BIND_PLAYER_MESSAGE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_BIND_PLAYER_MESSAGE_FWD_HPP_INCLUDED

#include <sanguis/messages/make_message_id_fwd.hpp>
#include <sanguis/messages/types/message_fwd.hpp>


namespace sanguis
{
namespace messages
{

// For now, player messages are nothing special. This might be changed if
// support for multiple players on one client may be added.
template<
	sanguis::messages::types::message Msg
>
using bind_player_message
=
sanguis::messages::make_message_id<
	Msg
>;

}
}

#endif
