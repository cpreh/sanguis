#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/player_center_callback.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
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
		sanguis::load::auras::context &,
		sanguis::client::draw2d::entities::model::load_parameters const &,
		sanguis::client::draw2d::player_center_callback const &,
		sanguis::client::draw2d::collide_callback const &,
		sanguis::aura_type_vector const &,
		sanguis::buff_type_vector const &
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

	sanguis::client::draw2d::player_center_callback const player_center_callback_;

	sanguis::client::draw2d::collide_callback const collide_;

	sanguis::client::draw2d::speed desired_speed_;
};

}
}
}
}

#endif
