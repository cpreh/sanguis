#include "converter.hpp"
#include "../messages/base.hpp"
#include "../messages/add.hpp"
#include "../messages/speed.hpp"
#include "../messages/move.hpp"
#include "../messages/remove.hpp"
#include "../messages/health.hpp"
#include "../messages/rotate.hpp"
#include "../messages/start_attacking.hpp"
#include "../messages/stop_attacking.hpp"

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::add>(const entity &e)
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
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::speed>(const entity &e)
{
	return new messages::speed(e.id(),e.abs_speed());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::move>(const entity &e)
{
	return new messages::move(e.id(),e.pos());
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

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::stop_attacking>(const entity &e)
{
	return new messages::stop_attacking(e.id());
}

template<>
sanguis::messages::base *sanguis::server::message_convert<sanguis::messages::start_attacking>(const entity &e)
{
	return new messages::stop_attacking(e.id());
}
