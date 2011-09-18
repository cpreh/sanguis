#ifndef SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef fcppt::function::object<
	void (
		server::player_id,
		messages::auto_ptr
	)
> unicast_callback;

}
}

#endif
