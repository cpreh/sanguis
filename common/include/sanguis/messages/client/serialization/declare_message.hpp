#ifndef SANGUIS_MESSAGES_CLIENT_SERIALIZATION_DECLARE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_DECLARE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/client/serialization/details.hpp> // IWYU pragma: keep
#include <sanguis/messages/client/types/alda_type.hpp> // IWYU pragma: keep
#include <alda/serialization/declare_message.hpp>

#define SANGUIS_MESSAGES_CLIENT_SERIALIZATION_DECLARE_MESSAGE(msg) \
  ALDA_SERIALIZATION_DECLARE_MESSAGE(sanguis::messages::client::types::alda_type, msg)

#endif
