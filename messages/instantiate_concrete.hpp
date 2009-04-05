#ifndef SANGUIS_MESSAGES_INSTANTIATE_CONCRETE_HPP_INCLUDED
#define SANGUIS_MESSAGES_INSTANTIATE_CONCRETE_HPP_INCLUDED

#include "concrete_impl.hpp"

#define SANGUIS_MESSAGES_INSTANTIATE_CONCRETE(msg)\
template class sanguis::messages::concrete<msg>;

#endif
