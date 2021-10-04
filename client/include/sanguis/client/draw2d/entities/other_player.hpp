#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_OTHER_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_OTHER_PLAYER_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/player.hpp>
#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities
{

class other_player
:
	public sanguis::client::draw2d::entities::player
{
	FCPPT_NONMOVABLE(
		other_player
	);
public:
	other_player(
		sanguis::client::load::auras::context_ref,
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::optional_primary_weapon_type,
		sanguis::weapon_status,
		sanguis::client::draw2d::speed const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::aura_type_vector &&,
		sanguis::buff_type_vector &&,
		sanguis::client::health_pair,
		sanguis::client::draw2d::entities::name const &
	);

	~other_player()
	override;
private:
	[[nodiscard]]
	sanguis::client::draw2d::entities::hover::optional_info
	hover() const
	override;

	sanguis::client::draw2d::entities::hover::name const name_;
};

}

#endif
