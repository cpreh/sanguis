#include "player.hpp"
#include "base_parameters.hpp"
#include "../get_dim.hpp"
#include "../../load/context.hpp"
#include "../level_calculate.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/console/console.hpp>

sanguis::server::entities::player::player(
	server::environment const &env,
	armor_array const &armor,
	net::id_type const net_id_,
	pos_type const &center_,
	space_unit const direction_,
	space_unit const angle_,
	property_map const &properties,
	string const &name_)
:
	entity_with_weapon(
		base_parameters(
			env,
			armor,
			center_,
			angle_,
			direction_,
			team::players,
			properties,
			entity_type::player,
			false,
			get_dim(
				env.load().models(),
				SGE_TEXT("player"),
				SGE_TEXT("bottom")))),
	net_id_(net_id_),
	name_(name_),
	exp_(static_cast<exp_type>(0)),
	level_(static_cast<level_type>(0)),
	level_delta_(static_cast<level_type>(0))
{}

sanguis::server::exp_type
sanguis::server::entities::player::exp() const
{
	return exp_;
}

void sanguis::server::entities::player::exp(
	exp_type const e)
{
	exp_ = e;
	level_type const
		old_level = level(),
		new_level = level_calculate(exp(), old_level);
	if (new_level > old_level)
	{
		level_delta_ += new_level - old_level;
		level_ = new_level;
		environment().level(*this, old_level);
	}
}

net::id_type
sanguis::server::entities::player::net_id() const
{
	return net_id_;
}

sanguis::server::string const
sanguis::server::entities::player::name() const
{
	return name_;
}

sanguis::server::level_type
sanguis::server::entities::player::level() const
{
	return level_;
}

sanguis::server::level_type
sanguis::server::entities::player::level_delta() const
{
	return level_delta_;
}

bool
sanguis::server::entities::player::perk_choosable(
	perk_type::type const p) const
{
	return perk_tree_.choosable(p);
}
