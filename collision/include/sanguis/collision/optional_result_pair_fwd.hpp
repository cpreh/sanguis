#ifndef SANGUIS_COLLISION_OPTIONAL_RESULT_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_OPTIONAL_RESULT_PAIR_FWD_HPP_INCLUDED

#include <sanguis/collision/result_pair_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis
{
namespace collision
{

typedef
fcppt::optional::object<
	sanguis::collision::result_pair
>
optional_result_pair;

}
}

#endif
