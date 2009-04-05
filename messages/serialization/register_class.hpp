#ifndef SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS_HPP_INCLUDED

#include "dispatcher_register_impl.hpp"
#include <boost/mpl/at.hpp>

#define SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS(context, type)\
namespace \
{ \
\
sanguis::messages::serialization::dispatcher_register<type> const \
register_class_tmp(\
	context);\
\
}

#endif
