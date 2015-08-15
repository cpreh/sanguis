#ifndef SANGUIS_CLIENT_PLAYER_HEALTH_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_PLAYER_HEALTH_CALLBACK_HPP_INCLUDED

#include <sanguis/client/optional_health_pair_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis
{
namespace client
{

typedef
fcppt::function<
	void(
		sanguis::client::optional_health_pair const &
	)
>
player_health_callback;

}
}

#endif
