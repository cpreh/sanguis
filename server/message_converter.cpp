/*
#include "message_converter.hpp"
#include "../messages/base.hpp"
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
*/
