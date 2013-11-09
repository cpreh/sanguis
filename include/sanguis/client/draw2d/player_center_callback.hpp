#ifndef SANGUIS_CLIENT_DRAW2D_PLAYER_CENTER_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_PLAYER_CENTER_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/optional_player_center_fwd.hpp>
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
		sanguis::client::draw2d::optional_player_center
	)
> player_center_callback;

}
}
}

#endif
