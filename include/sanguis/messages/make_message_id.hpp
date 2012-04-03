#ifndef SANGUIS_MESSAGES_MAKE_MESSAGE_ID_HPP_INCLUDED
#define SANGUIS_MESSAGES_MAKE_MESSAGE_ID_HPP_INCLUDED

#include <sanguis/messages/types/alda_type.hpp>
#include <sanguis/messages/types/message.hpp>
#include <alda/message/make_id.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sanguis
{
namespace messages
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	sanguis::messages::types::message::type Msg
>
struct make_message_id
:
alda::message::make_id<
	sanguis::messages::types::alda_type,
	Msg
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
