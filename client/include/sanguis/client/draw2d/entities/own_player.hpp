#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OWN_PLAYER_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/player_health_callback.hpp>
#include <sanguis/client/draw2d/collide_callback.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities
{

class own_player
:
	public sanguis::client::draw2d::entities::player
{
	FCPPT_NONMOVABLE(
		own_player
	);
public:
	own_player(
		sanguis::client::load::auras::context_ref,
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::draw2d::collide_callback &&,
		sanguis::client::player_health_callback &&,
		sanguis::optional_primary_weapon_type,
		sanguis::weapon_status,
		sanguis::client::draw2d::speed const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::aura_type_vector &&,
		sanguis::buff_type_vector &&,
		sanguis::client::health_pair
	);

	~own_player()
	override;
private:
	void
	health(
		sanguis::client::health
	)
	override;

	void
	max_health(
		sanguis::client::max_health
	)
	override;

	void
	speed(
		sanguis::client::draw2d::speed const &
	)
	override;

	using sanguis::client::draw2d::entities::player::speed;

	void
	update()
	override;

	void
	on_die()
	override;

	void
	update_health();

	sanguis::client::draw2d::collide_callback const collide_;

	sanguis::client::player_health_callback const player_health_callback_;

	sanguis::client::draw2d::speed desired_speed_;
};

}

#endif
