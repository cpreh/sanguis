#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/dim_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class player
:
	public sanguis::client::draw2d::entities::with_buffs_auras_model
{
	FCPPT_NONMOVABLE(
		player
	);
public:
	player(
		sanguis::client::load::auras::context_ref,
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::optional_primary_weapon_type,
		sanguis::weapon_status,
		sanguis::client::draw2d::speed const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::aura_type_vector &&,
		sanguis::buff_type_vector &&,
		sanguis::client::health_pair
	);

	~player()
	override;

	void
	orientation(
		sanguis::client::draw2d::sprite::rotation
	)
	override;

	void
	speed(
		sanguis::client::draw2d::speed const &
	)
	override;
protected:
	void
	update()
	override;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::dim
	bounding_dim() const;

	using sanguis::client::draw2d::entities::container::orientation;

	using sanguis::client::draw2d::entities::container::speed;
};

}
}
}
}

#endif
