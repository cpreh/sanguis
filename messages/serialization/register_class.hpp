#ifndef SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS_HPP_INCLUDED

#define SANGUIS_MESSAGES_SERIALIZATION_REGISTER_CLASS(context, id, type)\
namespace \
{ \
\
dispatch_register<type> register_class_tmp(context, id);\
\
}

#endif
