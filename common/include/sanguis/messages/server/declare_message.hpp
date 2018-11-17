#ifndef SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/serialization/declare_message.hpp>
#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/message/declare_concrete.hpp>


#define SANGUIS_MESSAGES_SERVER_DECLARE_MESSAGE(\
	msg\
) \
SANGUIS_MESSAGES_SERVER_SERIALIZATION_DECLARE_MESSAGE(\
	msg\
); \
ALDA_MESSAGE_DECLARE_CONCRETE(\
	sanguis::messages::server::types::alda_type,\
	msg\
)\

#endif
