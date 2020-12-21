#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/enemy_kind_fwd.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/create_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/name_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/client/load/auras/context_ref.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class enemy
:
	public sanguis::client::draw2d::entities::with_buffs_auras_model
{
	FCPPT_NONMOVABLE(
		enemy
	);
public:
	enemy(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::load::auras::context_ref,
		sanguis::creator::enemy_type,
		sanguis::enemy_kind,
		sanguis::optional_primary_weapon_type,
		sanguis::weapon_status,
		sanguis::client::draw2d::speed const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::aura_type_vector &&,
		sanguis::buff_type_vector &&,
		sanguis::client::draw2d::entities::name const &,
		sanguis::client::health_pair
	);

	~enemy()
	override;
private:
	void
	on_create(
		sanguis::client::draw2d::entities::create_parameters const &
	)
	override;

	[[nodiscard]]
	sanguis::client::draw2d::entities::hover::optional_info
	hover() const
	override;

	sanguis::creator::enemy_type const enemy_type_;

	sanguis::client::draw2d::entities::hover::name const name_;
};

}
}
}
}

#endif
