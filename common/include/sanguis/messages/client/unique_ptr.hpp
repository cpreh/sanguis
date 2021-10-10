#ifndef SANGUIS_MESSAGES_CLIENT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/message/base_unique_ptr.hpp>

namespace sanguis::messages::client
{

using unique_ptr = alda::message::base_unique_ptr<sanguis::messages::client::types::alda_type>;

}

#endif
