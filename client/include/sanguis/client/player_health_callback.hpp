#ifndef SANGUIS_CLIENT_PLAYER_HEALTH_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PLAYER_HEALTH_CALLBACK_HPP_INCLUDED

#include <sanguis/client/optional_health_pair_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace client
{

using
player_health_callback
=
fcppt::function<
	void(
		sanguis::client::optional_health_pair const &
	)
>;

}
}

#endif
