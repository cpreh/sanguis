#include "zombie.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include <sge/math/vec_dim.hpp>

sge::con::var<sanguis::messages::space_unit> sanguis::server::zombie::running_speed(SGE_TEXT("zombie_speed"),messages::mu(60));

sanguis::server::zombie::zombie(
	const entity_id id,
	const messages::pos_type &center_,
	const messages::space_unit direction_,
	const messages::space_unit speed_,
	const messages::space_unit angle_,
	const messages::space_unit health_,
	const messages::space_unit max_health_)
	: entity(id,center_ - dim()/messages::mu(2),angle_,direction_,speed_),
		health_(health_),
		max_health_(max_health_)
{}

sanguis::messages::dim_type sanguis::server::zombie::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["zombie"]["bottom"][weapon_type::none][animation_type::none].get().dim());
}

sanguis::messages::space_unit sanguis::server::zombie::max_speed() const
{
	return running_speed.value();
}
