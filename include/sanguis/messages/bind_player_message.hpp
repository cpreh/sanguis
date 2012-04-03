#ifndef SANGUIS_MESSAGES_BIND_PLAYER_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_BIND_PLAYER_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/make_message_id.hpp>
#include <sanguis/messages/types/message.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sanguis
{
namespace messages
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

// for now, player messages are nothing special
// this might be changed if support for multiple players on one client may be added
template<
	types::message::type Msg
>
struct bind_player_message
:
messages::make_message_id<
	Msg
>
{};

FCPPT_PP_POP_WARNING

}
}

#endif
