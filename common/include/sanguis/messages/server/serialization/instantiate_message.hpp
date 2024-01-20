#ifndef SANGUIS_MESSAGES_SERVER_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/server/serialization/global_context.hpp> // IWYU pragma: keep
#include <sanguis/messages/server/types/alda_type.hpp> // IWYU pragma: keep
#include <alda/serialization/instantiate_message.hpp>
#include <alda/serialization/register_message.hpp>

#define SANGUIS_MESSAGES_SERVER_SERIALIZATION_INSTANTIATE_MESSAGE(msg) \
  ALDA_SERIALIZATION_INSTANTIATE_MESSAGE(sanguis::messages::server::types::alda_type, msg); \
  namespace \
  { \
\
  ALDA_SERIALIZATION_REGISTER_MESSAGE( \
      sanguis::messages::server::serialization::global_context(), \
      sanguis::messages::server::types::alda_type, \
      msg); \
  }

#endif
