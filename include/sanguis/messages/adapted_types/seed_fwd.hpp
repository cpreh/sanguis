#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_SEED_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_SEED_FWD_HPP_INCLUDED

#include <sanguis/creator/seed_fwd.hpp>
#include <alda/bindings/fundamental_strong_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

typedef
alda::bindings::fundamental_strong<
	sanguis::creator::seed
>
seed;

}
}
}

#endif
