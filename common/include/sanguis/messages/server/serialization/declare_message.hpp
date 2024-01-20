#ifndef SANGUIS_MESSAGES_SERVER_SERIALIZATION_DECLARE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_DECLARE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/server/serialization/details.hpp> // IWYU pragma: keep
#include <sanguis/messages/server/types/alda_type.hpp> // IWYU pragma: keep
#include <alda/serialization/declare_message.hpp>

#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_DECLARE_MESSAGE(msg) \
  ALDA_SERIALIZATION_DECLARE_MESSAGE(sanguis::messages::server::types::alda_type, msg)

#endif
