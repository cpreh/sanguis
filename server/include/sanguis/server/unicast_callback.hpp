#ifndef SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED
#define SANGUIS_SERVER_UNICAST_CALLBACK_HPP_INCLUDED

#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/server/player_id.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace server
{

typedef
fcppt::function<
	void (
		sanguis::server::player_id,
		sanguis::messages::server::base const &
	)
>
unicast_callback;

}
}

#endif
