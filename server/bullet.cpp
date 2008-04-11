#include "bullet.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include "../resolution.hpp"
#include <sge/math/rect_impl.hpp>
#include <sge/math/vec_dim.hpp>
#include <sge/math/rect_util.hpp>

sge::con::var<sanguis::messages::space_unit> sanguis::server::bullet::bullet_speed(SGE_TEXT("bullet_speed"),static_cast<sanguis::messages::space_unit>(200));

sanguis::server::bullet::bullet(const entity_id id,const messages::pos_type &center_,const messages::space_unit direction_,const messages::space_unit angle_) 
	: entity(
			id,
			center_ - dim()/static_cast<messages::space_unit>(2),
			angle_,
			direction_,
			static_cast<messages::space_unit>(1)),
		visible_(true) 
{}

sanguis::messages::dim_type sanguis::server::bullet::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["bullet"]["default"][weapon_type::none][animation_type::none].get().dim());
}

sanguis::messages::space_unit sanguis::server::bullet::max_speed() const
{
	return bullet_speed.value();
}

void sanguis::server::bullet::update(const time_type)
{
	// bullet not visible anymore?
	visible_ = sge::math::intersects(
		sge::math::rect(
			sge::su(-0.5)*sge::su(resolution().w()),
			sge::su(-0.5)*sge::su(resolution().h()),
			sge::su(1.5)*sge::su(resolution().w()),
			sge::su(1.5)*sge::su(resolution().h())),
		sge::math::structure_cast<sge::space_unit>(center()));
}
