#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_ENUM_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_ENUM_FWD_HPP_INCLUDED

#include <sanguis/messages/types/enum.hpp>
#include <alda/bindings/enum_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

template<
	typename Enum
>
using enum_
=
alda::bindings::enum_<
	Enum,
	sanguis::messages::types::enum_
>;

}
}
}

#endif
