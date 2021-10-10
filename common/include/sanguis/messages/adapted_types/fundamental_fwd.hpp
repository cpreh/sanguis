#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_FUNDAMENTAL_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_FUNDAMENTAL_FWD_HPP_INCLUDED

#include <alda/bindings/fundamental_decl.hpp>

namespace sanguis::messages::adapted_types
{

template <typename Type>
// TODO(philipp): Check if Type has one byte
using fundamental = alda::bindings::fundamental<Type>;

}

#endif
