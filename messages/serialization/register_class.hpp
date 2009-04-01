#ifndef SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS_HPP_INCLUDED

#include "dispatcher_register_impl.hpp"

#define SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS(context, id, type)\
namespace \
{ \
\
dispatcher_register<type> const\
register_class_tmp(\
	context,\
	id);\
\
}

#endif
