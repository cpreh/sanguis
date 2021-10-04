#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_WORLD_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_WORLD_ID_FWD_HPP_INCLUDED

#include <sanguis/world_id_fwd.hpp>
#include <sanguis/world_id_type.hpp>
#include <sanguis/messages/adapted_types/unsigned_fwd.hpp>
#include <alda/bindings/strong_typedef_decl.hpp>


namespace sanguis::messages::adapted_types
{

using
world_id
=
alda::bindings::strong_typedef<
	sanguis::world_id,
	sanguis::messages::adapted_types::unsigned_<
		sanguis::world_id_type
	>
>;

}

#endif
