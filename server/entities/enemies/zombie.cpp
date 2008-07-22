#include "zombie.hpp"
#include "../../get_dim.hpp"
#include "../../ai/simple.hpp"
#include "../../weapons/factory.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/console/console.hpp>

namespace
{
sge::con::var<sanguis::messages::space_unit> zombie_damage(SGE_TEXT("zombie_damage"),sanguis::messages::mu(5));
}

sanguis::server::entities::enemies::zombie::zombie(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const &center_,
	messages::space_unit const direction_,
	messages::space_unit const angle_,
	property_map const &properties)
	: enemy(
		enemy_type::zombie,
		env,
		armor,
		center_ - dim()/messages::mu(2),
		angle_,
		direction_,
		team::monsters,
		properties,
		ai::ai_ptr(
			new ai::simple(
				*this)))
{
	add_weapon(weapons::create(
			weapon_type::melee,
			get_environment()));
	
	change_weapon(weapon_type::melee);
}

bool sanguis::server::entities::enemies::zombie::invulnerable() const
{
	return false;
}

sanguis::messages::dim_type const sanguis::server::entities::enemies::zombie::dim() const
{
	return get_dim(
		SGE_TEXT("zombie00"),
		SGE_TEXT("default")
		);
}

sanguis::messages::exp_type sanguis::server::entities::enemies::zombie::exp() const
{
	return static_cast<messages::exp_type>(10);
}
