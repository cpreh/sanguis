#ifndef SANGUIS_SERVER_MESSAGE_CONVERTER_HPP_INCLUDED
#define SANGUIS_SERVER_MESSAGE_CONVERTER_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../messages/fwd.hpp"
#include "entity.hpp"

namespace sanguis
{
namespace server
{
template<typename T>
messages::base *message_convert(const entity &);

template<>
messages::base *message_convert<messages::add>(const entity &e);
template<>
messages::base *message_convert<messages::speed>(const entity &e);
template<>
messages::base *message_convert<messages::move>(const entity &e);
template<>
messages::base *message_convert<messages::health>(const entity &e);
template<>
messages::base *message_convert<messages::remove>(const entity &e);
template<>
messages::base *message_convert<messages::rotate>(const entity &e);
template<>
messages::base *message_convert<messages::stop_attacking>(const entity &e);
template<>
messages::base *message_convert<messages::start_attacking>(const entity &e);
}
}

#endif
