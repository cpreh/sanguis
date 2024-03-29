#ifndef SANGUIS_MESSAGES_SERVER_BASE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_BASE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/message/base_fwd.hpp>

namespace sanguis::messages::server
{

using base = alda::message::base<sanguis::messages::server::types::alda_type>;

}

#endif
