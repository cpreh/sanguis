#include "message_converter.hpp"
#include "../messages/base.hpp"
#include "../messages/add.hpp"
#include "../messages/add_enemy.hpp"
#include "../messages/add_pickup.hpp"
#include "../messages/add_decoration.hpp"
#include "../messages/add_projectile.hpp"
#include "../messages/add_weapon_pickup.hpp"
#include "../messages/speed.hpp"
#include "../messages/move.hpp"
#include "../messages/remove.hpp"
#include "../messages/health.hpp"
#include "../messages/rotate.hpp"
#include "../messages/start_attacking.hpp"
#include "../messages/stop_attacking.hpp"
#include "../messages/start_reloading.hpp"
#include "../messages/stop_reloading.hpp"
#include "entities/entity.hpp"
#include "entities/decoration.hpp"
#include "entities/enemies/enemy.hpp"
#include "entities/pickups/pickup.hpp"
#include "entities/pickups/weapon.hpp"
#include "entities/projectiles/projectile.hpp"

sanguis::messages::auto_ptr
sanguis::server::message_convert(
	entities::enemies::enemy const &e)
{
	return messages::auto_ptr(
		new messages::add_enemy(
			e.id(),
			e.etype(),
			e.pos(),
			e.angle(),
			e.abs_speed(),
			e.health(),
			e.max_health(),
			e.dim()));
}

sanguis::messages::auto_ptr
sanguis::server::message_convert(
	entities::pickups::pickup const &e)
{
	return messages::auto_ptr(
		new messages::add_pickup(
			e.id(),
			e.ptype(),
			e.pos(),
			e.angle(),
			e.health(),
			e.max_health(),
			e.dim())); // FIXME: should we care about speed though?
}

sanguis::messages::auto_ptr
sanguis::server::message_convert(
	entities::decoration const &e)
{
	return messages::auto_ptr(
		new messages::add_decoration(
			e.id(),
			e.dtype(),
			e.pos(),
			e.angle(),
			e.health(),
			e.max_health(),
			e.dim()));
}

sanguis::messages::auto_ptr
sanguis::server::message_convert(
	entities::projectiles::projectile const &e)
{
	return messages::auto_ptr(
		new messages::add_projectile(
			e.id(),
			e.ptype(),
			e.pos(),
			e.angle(),
			e.abs_speed(),
			e.health(),
			e.max_health(),
			e.dim()));
}

sanguis::messages::auto_ptr
sanguis::server::message_convert(
	entities::pickups::weapon const &e)
{
	return messages::auto_ptr(
		new messages::add_weapon_pickup(
			e.id(),
			e.wtype(),
			e.pos(),
			e.angle(),
			e.health(),
			e.max_health(),
			e.dim()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::add>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::add(
			e.id(),
			e.type(),
			e.pos(),
			e.angle(),
			e.abs_speed(),
			e.health(),
			e.max_health(),
			e.dim()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::speed>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::speed(
			e.id(),
			e.abs_speed()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::move>(entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::move(
			e.id(),
			e.pos()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::health>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::health(
			e.id(),
			e.health()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::remove>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::remove(
			e.id()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::rotate>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::rotate(
			e.id(),
			e.angle()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::stop_attacking>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::stop_attacking(
			e.id()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::start_attacking>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::start_attacking(
			e.id()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::stop_reloading>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::stop_reloading(
			e.id()));
}

template<>
sanguis::messages::auto_ptr
sanguis::server::message_convert<sanguis::messages::start_reloading>(
	entities::entity const &e)
{
	return messages::auto_ptr(
		new messages::start_reloading(
			e.id()));
}
