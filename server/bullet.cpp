#include "bullet.hpp"
#include <sge/math/rect_impl.hpp>
#include <sge/math/rect_util.hpp>

sge::con::var<sanguis::messages::space_unit> sanguis::server::bullet::bullet_speed(SGE_TEXT("bullet_speed"),static_cast<sanguis::messages::space_unit>(0.4));

sanguis::server::bullet::bullet(const entity_id id,const messages::pos_type &center_,const messages::pos_type &direction_,const messages::space_unit angle_) 
	: entity(id),center_(center_),direction_(direction_),angle_(angle_),visible_(true) {}

sanguis::messages::pos_type sanguis::server::bullet::speed() const
{
	return direction_ * bullet_speed.value();
}

void sanguis::server::bullet::update(const time_type delta)
{
	center_ += speed() * delta;
	
	// bullet not visible anymore?
	visible_ = sge::math::intersects(
		sge::math::rect(sge::su(-0.5),sge::su(-0.5),sge::su(1.5),sge::su(1.5)),
		center_);

}
