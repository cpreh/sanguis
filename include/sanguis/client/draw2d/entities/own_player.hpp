#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED

#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/transform_callback.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
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
	public sanguis::client::draw2d::entities::player
{
	FCPPT_NONCOPYABLE(
		own_player
	);
public:
	own_player(
		sanguis::client::draw2d::entities::model::parameters const &,
		sanguis::client::draw2d::transform_callback const &,
		sanguis::client::draw2d::collide_callback const &
	);

	~own_player();
private:
	void
	speed(
		sanguis::client::draw2d::speed const &
	)
	override;

	using sanguis::client::draw2d::entities::player::speed;

	void
	update()
	override;

	sanguis::client::draw2d::transform_callback const transform_;

	sanguis::client::draw2d::collide_callback const collide_;

	sanguis::client::draw2d::speed desired_speed_;
};

}
}
}
}

#endif
