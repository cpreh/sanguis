#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class own_player
:
	public player
{
	FCPPT_NONCOPYABLE(
		own_player
	);
public:
	own_player(
		model::parameters const &,
		draw2d::transform_callback const &
	);

	~own_player();
private:
	void
	update();

	draw2d::transform_callback const transform_;
};

}
}
}
}

#endif
