#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED

#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/rotation_fwd.hpp>
#include <sanguis/load/model/path_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class aoe_bullet
:
	public sanguis::client::draw2d::entities::model::object
{
	FCPPT_NONMOVABLE(
		aoe_bullet
	);
public:
	aoe_bullet(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::client::draw2d::insert_own_callback &&,
		sanguis::load::model::path &&,
		sanguis::client::draw2d::speed const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::client::draw2d::aoe
	);

	~aoe_bullet()
	override;
private:
	void
	on_die()
	override;

	sanguis::client::draw2d::entities::load_parameters const load_parameters_;

	sanguis::client::draw2d::insert_own_callback const insert_;

	sanguis::client::draw2d::aoe const aoe_;

};

}
}
}
}

#endif
