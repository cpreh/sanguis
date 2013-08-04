#ifndef SANGUIS_MESSAGES_MAKE_MESSAGE_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_MESSAGE_ID_FWD_HPP_INCLUDED

#include <sanguis/messages/types/alda_type.hpp>
#include <sanguis/messages/types/message_fwd.hpp>
#include <alda/message/make_id_fwd.hpp>


namespace sanguis
{
namespace messages
{

template<
	sanguis::messages::types::message Msg
>
using make_message_id
=
alda::message::make_id<
	sanguis::messages::types::alda_type,
	Msg
>;

}
}

#endif
