#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_AOE_BULLET_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/insert_own_callback.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/load/model/collection_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		aoe_bullet
	);
public:
	aoe_bullet(
		sanguis::client::draw2d::entities::model::load_parameters const &,
		sanguis::client::draw2d::insert_own_callback const &,
		sanguis::client::draw2d::entities::model::name const &,
		sanguis::client::draw2d::aoe
	);

	~aoe_bullet();
private:
	void
	on_die()
	override;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::load::model::collection const &model_collection_;

	sanguis::client::draw2d::sprite::normal::system &normal_system_;

	sanguis::client::draw2d::insert_own_callback const insert_;

	sanguis::client::draw2d::aoe const aoe_;

};

}
}
}
}

#endif
