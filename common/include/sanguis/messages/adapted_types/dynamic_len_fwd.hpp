#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_DYNAMIC_LEN_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_DYNAMIC_LEN_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/length_fwd.hpp>
#include <alda/bindings/dynamic_len_decl.hpp>

namespace sanguis::messages::adapted_types
{

template <typename Type, typename Adapted>
using dynamic_len =
    alda::bindings::dynamic_len<Type, Adapted, sanguis::messages::adapted_types::length>;

}

#endif
