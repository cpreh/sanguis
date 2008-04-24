#include "player.hpp"
#include "../../load/model/collection.hpp"
#include "../../load/model/singleton.hpp"
#include <sge/math/vec_dim.hpp>
#include <sge/console/console.hpp>

namespace
{
sge::con::var<sanguis::messages::space_unit> running_speed(SGE_TEXT("player_speed"),sanguis::messages::mu(60));
}

sanguis::server::entities::player::player(
	const send_callback &send_callback_,
	const insert_callback &insert_callback_,
	const net::id_type net_id_,
	const messages::pos_type &center_,
	const messages::space_unit direction_,
	const messages::space_unit speed_,
	const messages::space_unit angle_,
	const messages::space_unit health_,
	const messages::space_unit max_health_,
	const messages::string &name_)
	: entity_with_weapon(
		send_callback_,
		insert_callback_,
		center_ - dim()/messages::mu(2),
		angle_,
		direction_,
		health_,
		max_health_,
		team::players,
		speed_),
	net_id_(net_id_),
	name_(name_)
{}

void sanguis::server::entities::player::attack(entity &) {}

bool sanguis::server::entities::player::invulnerable() const
{
	return false;
}

sanguis::messages::dim_type sanguis::server::entities::player::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["player"]["bottom"][weapon_type::pistol][animation_type::walking].get().dim());
}

sanguis::messages::space_unit sanguis::server::entities::player::max_speed() const
{
	return running_speed.value();
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
