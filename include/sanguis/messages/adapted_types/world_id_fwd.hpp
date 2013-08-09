#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_WORLD_ID_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_WORLD_ID_FWD_HPP_INCLUDED

#include <sanguis/world_id_fwd.hpp>
#include <sanguis/world_id_type.hpp>
#include <alda/bindings/strong_typedef_decl.hpp>
#include <alda/bindings/unsigned_decl.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::strong_typedef<
	sanguis::world_id,
	alda::bindings::unsigned_<
		sanguis::world_id_type
	>
>
world_id;

}
}
}

#endif
