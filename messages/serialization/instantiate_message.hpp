#ifndef SANGUIS_MESSAGEES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGEES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include "dispatcher_impl.hpp"
#include "dispatcher_register_impl.hpp"
#include "reader_impl.hpp"

#define SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE(msg)\
template class sanguis::messages::serialization::dispatcher<msg>;\
template class sanguis::messages::serialization::dispatcher_register<msg>;\
template class sanguis::messages::serialization::reader<msg>;

#endif
