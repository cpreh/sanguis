#ifndef SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/serialization/instantiate_message.hpp>
#include <sanguis/messages/types/alda_type.hpp>
#include <alda/message/instantiate_concrete.hpp>


#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE(\
	msg\
) \
SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE(\
	msg\
)\
ALDA_MESSAGE_INSTANTIATE_CONCRETE(\
	sanguis::messages::types::alda_type,\
	msg\
)\

#endif
