#ifndef SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace server
{

typedef fcppt::function::object<
	void (
		server::player_id,
		messages::base const &
	)
> unicast_callback;

}
}

#endif
