#ifndef SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/global_context.hpp>
#include <sanguis/messages/serialization/register_class.hpp>
#include <sanguis/messages/serialization/instantiate_message.hpp>
#include <sanguis/messages/instantiate_concrete.hpp>

#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE(msg) \
SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS(sanguis::messages::global_context(), msg) \
SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE(msg) \
SANGUIS_MESSAGES_INSTANTIATE_CONCRETE(msg)

#endif
