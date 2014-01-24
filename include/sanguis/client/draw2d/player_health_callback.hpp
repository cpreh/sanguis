#ifndef SANGUIS_CLIENT_DRAW2D_PLAYER_HEALTH_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PLAYER_HEALTH_CALLBACK_HPP_INCLUDED

#include <sanguis/client/health_pair_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef std::function<
	void(
		sanguis::client::health_pair const &
	)
> player_health_callback;

}
}
}

#endif
