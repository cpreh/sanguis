#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_SEED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_SEED_FWD_HPP_INCLUDED

#include <sanguis/creator/seed_fwd.hpp>
#include <sanguis/creator/seed_type.hpp>
#include <sanguis/messages/adapted_types/unsigned_fwd.hpp>
#include <alda/bindings/strong_typedef_decl.hpp>


namespace sanguis::messages::adapted_types
{

using
seed
=
alda::bindings::strong_typedef<
	sanguis::creator::seed,
	sanguis::messages::adapted_types::unsigned_<
		sanguis::creator::seed_type
	>
>;

}

#endif
