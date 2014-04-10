#ifndef SANGUIS_MESSAGES_CLIENT_CONCRETE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_CONCRETE_FWD_HPP_INCLUDED

#include <alda/message/concrete_fwd.hpp>
#include <sanguis/messages/client/types/alda_type_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace client
{

template<
	typename T
>
using
concrete
=
alda::message::concrete<
	sanguis::messages::client::types::alda_type,
	T
>;

}
}
}

#endif
