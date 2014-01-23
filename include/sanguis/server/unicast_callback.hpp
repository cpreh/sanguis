#ifndef SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{

typedef std::function<
	void (
		sanguis::server::player_id,
		sanguis::messages::server::base const &
	)
> unicast_callback;

}
}

#endif
