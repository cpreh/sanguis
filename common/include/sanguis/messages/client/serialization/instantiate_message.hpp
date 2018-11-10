#ifndef SANGUIS_MESSAGES_CLIENT_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/client/serialization/global_context.hpp>
#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>


#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_INSTANTIATE_MESSAGE(\
	msg\
)\
ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(\
	sanguis::messages::client::types::alda_type,\
	msg\
);\
namespace \
{\
\
ALDA_SERIALIZATION_REGISTER_MESSAGE(\
	sanguis::messages::client::serialization::global_context(),\
	sanguis::messages::client::types::alda_type,\
	msg\
);\
\
}

#endif
