#ifndef SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED
#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE_HPP_INCLUDED

#include "global_context.hpp"
#include "serialization/register_class.hpp"
#include <boost/mpl/at.hpp>

#define SANGUIS_MESSAGES_INSTANTIATE_MESSAGE(msg)\
SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS(global_context(), boost::mpl::at_c<msg::memory_type::types, 0>::value, msg)

#endif
