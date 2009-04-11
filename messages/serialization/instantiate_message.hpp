#ifndef SANGUIS_MESSAGEES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGEES_SERIALIZATION_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include "dispatcher_impl.hpp"
#include "dispatcher_register_impl.hpp"
#include "reader_impl.hpp"
#include "../auto_ptr.hpp"

#define SANGUIS_MESSAGES_SERIALIZATION_INSTANTIATE_MESSAGE(msg)\
template struct sanguis::messages::serialization::dispatcher<msg>; \
template struct sanguis::messages::serialization::dispatcher_register<msg>; \
template sanguis::messages::auto_ptr sanguis::messages::serialization::reader::operator()<msg>() const;

#endif
