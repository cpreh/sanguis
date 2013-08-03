#ifndef SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/global_context.hpp>
#include <sanguis/messages/types/alda_type.hpp>
#include <alda/message/instantiate_concrete.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>


#define SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE(\
	msg\
)\
ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(\
	sanguis::messages::types::alda_type,\
	msg\
);\
namespace \
{\
\
ALDA_SERIALIZATION_REGISTER_MESSAGE(\
	sanguis::messages::global_context(),\
	sanguis::messages::types::alda_type,\
	msg\
);\
\
}

#endif
