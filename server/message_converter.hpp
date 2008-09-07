#ifndef SANGUIS_SERVER_MESSAGE_CONVERTER_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERTER_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../messages/fwd.hpp"
#include "entities/entity_fwd.hpp"
#include "entities/enemies/fwd.hpp"
#include "entities/pickups/fwd.hpp"
#include "entities/projectiles/fwd.hpp"

namespace sanguis
{
namespace server
{

messages::auto_ptr
message_convert(
	entities::enemies::enemy const &e);

messages::auto_ptr
message_convert(
	entities::pickups::pickup const &e);

messages::auto_ptr
message_convert(
	entities::projectiles::projectile const &e);

messages::auto_ptr
message_convert(
	entities::pickups::weapon const &e);

template<typename T>
messages::auto_ptr message_convert(entities::entity const &);

template<>
messages::auto_ptr
message_convert<messages::add>(
	entities::entity const &e);

template<>
messages::auto_ptr message_convert<messages::speed>(const entities::entity &e);
template<>
messages::auto_ptr message_convert<messages::move>(const entities::entity &e);
template<>
messages::auto_ptr message_convert<messages::health>(const entities::entity &e);
template<>
messages::auto_ptr message_convert<messages::remove>(const entities::entity &e);
template<>
messages::auto_ptr message_convert<messages::rotate>(const entities::entity &e);
template<>
messages::auto_ptr message_convert<messages::stop_attacking>(const entities::entity &e);
template<>
messages::auto_ptr message_convert<messages::start_attacking>(const entities::entity &e);

}
}

#endif
