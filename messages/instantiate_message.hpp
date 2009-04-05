#ifndef SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include "global_context.hpp"
#include "serialization/register_class.hpp"
#include "serialization/instantiate_message.hpp"
#include "instantiate_concrete.hpp"

#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE(msg) \
SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS(sanguis::messages::global_context(), msg) \
SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE(msg) \
SANGUIS_MESSAGES_INSTANTIATE_CONCRETE(msg)

#endif
