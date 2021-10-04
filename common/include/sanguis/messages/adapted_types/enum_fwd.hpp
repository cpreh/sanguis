#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_ENUM_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_ENUM_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/unsigned_fwd.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <alda/bindings/enum_decl.hpp>


namespace sanguis::messages::adapted_types
{

template<
	typename Enum
>
using enum_
=
alda::bindings::enum_<
	Enum,
	sanguis::messages::adapted_types::unsigned_<
		sanguis::messages::types::enum_
	>
>;

}

#endif
