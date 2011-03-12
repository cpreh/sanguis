#ifndef SANGUIS_MESSAGES_BIND_PLAYER_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_BIND_PLAYER_MESSAGE_HPP_INCLUDED

#include "make_message_id.hpp"
#include "types/message.hpp"

namespace sanguis
{
namespace messages
{

// for now, player messages are nothing special
// this might be changed if support for multiple players on one client may be added
template<
	types::message::type Msg
>
struct bind_player_message
:
make_message_id<
	Msg
>
{};

}
}

#endif
