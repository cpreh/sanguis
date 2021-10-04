#ifndef SANGUIS_MESSAGES_SERVER_CONCRETE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CONCRETE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/alda_type_fwd.hpp>
#include <alda/message/concrete_fwd.hpp>


namespace sanguis::messages::server
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

#endif
