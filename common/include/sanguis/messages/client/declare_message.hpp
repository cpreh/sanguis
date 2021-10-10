#ifndef SANGUIS_MESSAGES_CLIENT_DECLARE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_CLIENT_DECLARE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/serialization/declare_message.hpp>
#include <sanguis/messages/client/types/alda_type.hpp>
#include <alda/message/declare_concrete.hpp>

#define SANGUIS_MESSAGES_CLIENT_DECLARE_MESSAGE(msg) \
  SANGUIS_MESSAGES_CLIENT_SERIALIZATION_DECLARE_MESSAGE(msg); \
  ALDA_MESSAGE_DECLARE_CONCRETE(sanguis::messages::client::types::alda_type, msg)

#endif
