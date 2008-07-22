#ifndef SANGUIS_SERVER_MESSAGE_CONVERTER_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERTER_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../messages/fwd.hpp"
#include "entities/entity_fwd.hpp"

namespace sanguis
{
namespace server
{
// FIXME: this should return an auto_ptr to messages::base

template<typename T>
messages::base *message_convert(const entities::entity &);

template<>
messages::base *message_convert<messages::add>(const entities::entity &e);
template<>
messages::base *message_convert<messages::add_enemy>(const entities::entity &e);
template<>
messages::base *message_convert<messages::add_pickup>(const entities::entity &e);
template<>
messages::base *message_convert<messages::add_weapon_pickup>(const entities::entity &e);
template<>
messages::base *message_convert<messages::speed>(const entities::entity &e);
template<>
messages::base *message_convert<messages::move>(const entities::entity &e);
template<>
messages::base *message_convert<messages::health>(const entities::entity &e);
template<>
messages::base *message_convert<messages::remove>(const entities::entity &e);
template<>
messages::base *message_convert<messages::rotate>(const entities::entity &e);
template<>
messages::base *message_convert<messages::stop_attacking>(const entities::entity &e);
template<>
messages::base *message_convert<messages::start_attacking>(const entities::entity &e);
}
}

#endif
