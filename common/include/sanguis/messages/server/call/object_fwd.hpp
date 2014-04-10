#ifndef SANGUIS_MESSAGES_SERVER_CALL_OBJECT_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_CALL_OBJECT_FWD_HPP_INCLUDED

#include <sanguis/messages/server/types/alda_type.hpp>
#include <alda/call/object_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace call
{

template<
	typename Messages,
	typename Callee
>
using object
=
alda::call::object<
	sanguis::messages::server::types::alda_type,
	Messages,
	Callee
>;

}
}
}
}

#endif
