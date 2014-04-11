#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_SEED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_SEED_FWD_HPP_INCLUDED

#include <sanguis/creator/seed_fwd.hpp>
#include <sanguis/creator/seed_type.hpp>
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
	sanguis::creator::seed,
	alda::bindings::unsigned_<
		sanguis::creator::seed_type
	>
>
seed;

}
}
}

#endif