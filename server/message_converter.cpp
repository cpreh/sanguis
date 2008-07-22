#include "message_converter.hpp"
#include "../messages/base.hpp"
#include "../messages/add.hpp"
#include "../messages/add_enemy.hpp"
#include "../messages/add_pickup.hpp"
#include "../messages/add_weapon_pickup.hpp"
#include "../messages/speed.hpp"
#include "../messages/move.hpp"
#include "../messages/remove.hpp"
#include "../messages/health.hpp"
#include "../messages/rotate.hpp"
#include "../messages/start_attacking.hpp"
#include "../messages/stop_attacking.hpp"
#include "entities/entity.hpp"
#include "entities/enemies/enemy.hpp"
#include "entities/pickups/pickup.hpp"
#include "entities/pickups/weapon.hpp"

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::add>(const entities::entity &e)
{
	return new messages::add(e.id(),
			e.type(),
			e.pos(),
			e.angle(),
			e.abs_speed(),
			e.health(),
			e.max_health(),
			e.dim());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::add_enemy>(const entities::entity &e)
{
	return new messages::add_enemy(
		e.id(),
		dynamic_cast<entities::enemies::enemy const &>(e).etype(),
		e.pos(),
		e.angle(),
		e.abs_speed(),
		e.health(),
		e.max_health(),
		e.dim());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::add_pickup>(const entities::entity &e)
{
	return new messages::add_pickup(
		e.id(),
		dynamic_cast<entities::pickups::pickup const &>(e).ptype(),
		e.pos(),
		e.angle(),
		e.dim()); // FIXME: should we care about speed and health though?
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::add_weapon_pickup>(const entities::entity &e)
{
	return new messages::add_weapon_pickup(
		e.id(),
		dynamic_cast<entities::pickups::weapon const &>(e).wtype(),
		e.pos(),
		e.angle(),
		e.dim());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::speed>(const entities::entity &e)
{
	return new messages::speed(e.id(),e.abs_speed());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::move>(const entities::entity &e)
{
	return new messages::move(e.id(),e.pos());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::health>(const entities::entity &e)
{
	return new messages::health(e.id(),e.health());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::remove>(const entities::entity &e)
{
	return new messages::remove(e.id());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::rotate>(const entities::entity &e)
{
	return new messages::rotate(e.id(),e.angle());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::stop_attacking>(const entities::entity &e)
{
	return new messages::stop_attacking(e.id());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::start_attacking>(const entities::entity &e)
{
	return new messages::start_attacking(e.id());
}
