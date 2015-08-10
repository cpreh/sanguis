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
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class other_player
:
	public sanguis::client::draw2d::entities::player
{
	FCPPT_NONCOPYABLE(
		other_player
	);
public:
	other_player(
		sanguis::client::load::auras::context &,
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::optional_primary_weapon_type,
		sanguis::weapon_status,
		sanguis::client::draw2d::speed,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::aura_type_vector const &,
		sanguis::buff_type_vector const &,
		sanguis::client::health_pair,
		sanguis::client::draw2d::entities::name const &
	);

	~other_player()
	override;
private:
	sanguis::client::draw2d::entities::hover::optional_info
	hover() const
	override;

	sanguis::client::draw2d::entities::hover::name const name_;
};

}
}
}
}

#endif
