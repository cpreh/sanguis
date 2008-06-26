#include "player.hpp"
#include "../../load/model/collection.hpp"
#include "../../load/model/singleton.hpp"
#include "../level_calculate.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/console/console.hpp>

sanguis::server::entities::player::player(
	environment const &env,
	armor_array const &armor,
	net::id_type const net_id_,
	messages::pos_type const &center_,
	messages::space_unit const direction_,
	messages::space_unit const angle_,
	property_map const &properties,
	messages::string const &name_)
	: entity_with_weapon(
		env,
		armor,
		center_ - dim()/messages::mu(2),
		angle_,
		direction_,
		team::players,
		properties),
	net_id_(net_id_),
	name_(name_),
	exp_(static_cast<messages::exp_type>(0)),
	level_(static_cast<messages::level_type>(0)),
	level_delta_(static_cast<messages::level_type>(0))
{}

void sanguis::server::entities::player::attack(entity &) {}

bool sanguis::server::entities::player::invulnerable() const
{
	return false;
}

sanguis::messages::dim_type const
sanguis::server::entities::player::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(
		load::model::singleton()
			["player"]
				["bottom"]
					[weapon_type::pistol]
						[animation_type::walking].get().dim());
}

sanguis::messages::exp_type sanguis::server::entities::player::exp() const
{
	return exp_;
}

void sanguis::server::entities::player::exp(const messages::exp_type e)
{
	exp_ = e;
	const messages::level_type old_level = level(),new_level = level_calculate(exp(),old_level);
	if (new_level > old_level)
	{
		level_delta_ += new_level - old_level;
		level_ = new_level;
		get_environment().level(*this,old_level);
	}
}

sanguis::entity_type::type
sanguis::server::entities::player::type() const
{
	return entity_type::player;
}

net::id_type
sanguis::server::entities::player::net_id() const
{
	return net_id_;
}

sanguis::messages::string
sanguis::server::entities::player::name() const
{
	return name_;
}

sanguis::messages::level_type sanguis::server::entities::player::level() const
{
	return level_;
}

sanguis::messages::level_type sanguis::server::entities::player::level_delta() const
{
	return level_delta_;
}
