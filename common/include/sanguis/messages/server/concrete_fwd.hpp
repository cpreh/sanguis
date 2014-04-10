#ifndef SANGUIS_MESSAGES_SERVER_CONCRETE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CONCRETE_FWD_HPP_INCLUDED

#include <alda/message/concrete_fwd.hpp>
#include <sanguis/messages/server/types/alda_type_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{

template<
	typename T
>
using
concrete
=
alda::message::concrete<
	sanguis::messages::server::types::alda_type,
	T
>;

}
}
}

#endif
