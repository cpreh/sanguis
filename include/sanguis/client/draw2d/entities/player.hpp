#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/model/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/dim_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
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

class player
:
	public sanguis::client::draw2d::entities::with_buffs_auras_model
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	player(
		sanguis::load::auras::context &,
		sanguis::client::draw2d::entities::model::load_parameters const &,
		sanguis::aura_type_vector const &,
		sanguis::buff_type_vector const &,
		sanguis::client::draw2d::entities::model::health_pair
	);

	~player();

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

	sanguis::client::draw2d::sprite::dim const
	bounding_dim() const;

	using sanguis::client::draw2d::entities::container::orientation;

	using sanguis::client::draw2d::entities::container::speed;
};

}
}
}
}

#endif
