#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ENEMY_HPP_INCLUDED

#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <sanguis/client/draw2d/entities/with_buffs_auras_model.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
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

class enemy
:
	public sanguis::client::draw2d::entities::with_buffs_auras_model
{
	FCPPT_NONCOPYABLE(
		enemy
	);
public:
	enemy(
		sanguis::client::draw2d::entities::model::load_parameters const &,
		sanguis::load::auras::context &,
		sanguis::creator::enemy_type,
		sanguis::aura_type_vector const &,
		sanguis::buff_type_vector const &,
		sanguis::client::draw2d::entities::name const &,
		sanguis::client::health_pair
	);

	~enemy();
private:
	sanguis::client::draw2d::entities::name
	name() const
	override;

	sanguis::client::draw2d::entities::name const name_;
};

}
}
}
}

#endif
