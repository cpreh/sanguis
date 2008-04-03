#include "converter.hpp"
#include "../messages/base.hpp"
#include "../messages/add.hpp"
#include "../messages/speed.hpp"
#include "../messages/move.hpp"
#include "../messages/remove.hpp"
#include "../messages/health.hpp"
#include "../messages/rotate.hpp"

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::add>(const entity &e)
{
	return new messages::add(e.id(),
			e.type(),
			e.center(),
			e.angle(),
			e.speed(),
			e.health(),
			e.max_health());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::speed>(const entity &e)
{
	return new messages::speed(e.id(),e.speed());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::move>(const entity &e)
{
	return new messages::move(e.id(),e.center());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::health>(const entity &e)
{
	return new messages::health(e.id(),e.health());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::remove>(const entity &e)
{
	return new messages::remove(e.id());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::rotate>(const entity &e)
{
	return new messages::rotate(e.id(),e.angle());
}
