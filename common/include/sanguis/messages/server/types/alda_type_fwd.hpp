#ifndef SANGUIS_MESSAGES_SERVER_TYPES_ALDA_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_ALDA_TYPE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/message.hpp>
#include <alda/type_enum_fwd.hpp>


namespace sanguis::messages::server::types
{

using
alda_type
=
alda::type_enum<
	sanguis::messages::server::types::message
>;

}

#endif
