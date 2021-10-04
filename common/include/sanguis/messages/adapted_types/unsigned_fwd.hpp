#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_UNSIGNED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_UNSIGNED_FWD_HPP_INCLUDED

#include <sanguis/messages/types/endianness.hpp>
#include <alda/bindings/unsigned_decl.hpp>


namespace sanguis::messages::adapted_types
{

template<
	typename Type
>
using
unsigned_
=
alda::bindings::unsigned_<
	Type,
	sanguis::messages::types::endianness()
>;

}

#endif
