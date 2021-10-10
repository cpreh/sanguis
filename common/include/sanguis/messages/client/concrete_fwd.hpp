#ifndef SANGUIS_MESSAGES_CLIENT_CONCRETE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CONCRETE_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/alda_type_fwd.hpp>
#include <alda/message/concrete_fwd.hpp>

namespace sanguis::messages::client
{

template <typename T>
using concrete = alda::message::concrete<sanguis::messages::client::types::alda_type, T>;

}

#endif
