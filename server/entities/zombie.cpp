#include "zombie.hpp"
#include "../get_dim.hpp"
#include "../ai/simple.hpp"
#include "../weapons/factory.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/console/console.hpp>

namespace
{
sge::con::var<sanguis::messages::space_unit> running_speed(SGE_TEXT("zombie_speed"),sanguis::messages::mu(40));
sge::con::var<sanguis::messages::space_unit> zombie_damage(SGE_TEXT("zombie_damage"),sanguis::messages::mu(5));
}

sanguis::server::entities::zombie::zombie(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &center_,
	messages::space_unit const direction_,
	messages::space_unit const speed_,
	messages::space_unit const angle_,
	messages::space_unit const health_,
	messages::space_unit const max_health_)
	: enemy(
			env,
			armor,
			center_ - dim()/messages::mu(2),
			angle_,
			direction_,
			health_,
			max_health_,
			team::monsters,
			speed_,
			ai::ai_ptr(
				new ai::simple(
					*this)))
{
	add_weapon(weapons::create(
				weapon_type::melee,
				get_environment()));
	
	change_weapon(weapon_type::melee);
}

bool sanguis::server::entities::zombie::invulnerable() const
{
	return false;
}

sanguis::messages::dim_type sanguis::server::entities::zombie::dim() const
{
	return get_dim(
		SGE_TEXT("zombie00"),
		SGE_TEXT("default")
		);
}

sanguis::messages::space_unit sanguis::server::entities::zombie::max_speed() const
{
	return running_speed.value();
}

sanguis::entity_type::type
sanguis::server::entities::zombie::type() const
{
	return entity_type::zombie;
}

sanguis::messages::exp_type sanguis::server::entities::zombie::exp() const
{
	return static_cast<messages::exp_type>(10);
}
