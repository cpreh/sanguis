#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_FUNDAMENTAL_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_FUNDAMENTAL_FWD_HPP_INCLUDED

#include <sanguis/messages/types/endianness.hpp>
#include <alda/bindings/fundamental_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

template<
	typename Type
>
using
fundamental
=
alda::bindings::fundamental<
	Type,
	sanguis::messages::types::endianness()
>;

}
}
}

#endif
