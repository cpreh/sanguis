#ifndef SANGUIS_MESSAGES_CLIENT_CALL_OBJECT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CALL_OBJECT_FWD_HPP_INCLUDED

#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/call/object_fwd.hpp>

namespace sanguis::messages::client::call
{

template <typename Messages, typename Callee>
using object = alda::call::object<sanguis::messages::client::types::alda_type, Messages, Callee>;

}

#endif
