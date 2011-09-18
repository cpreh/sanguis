#ifndef SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include <sanguis/messages/serialization/dispatcher_impl.hpp>
#include <sanguis/messages/serialization/dispatcher_register_impl.hpp>
#include <sanguis/messages/serialization/reader_impl.hpp>
#include <sanguis/messages/auto_ptr.hpp>

#define SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE(msg)\
template class sanguis::messages::serialization::dispatcher<msg>; \
template class sanguis::messages::serialization::dispatcher_register<msg>; \
template sanguis::messages::auto_ptr sanguis::messages::serialization::reader::operator()<msg>() const;

#endif
