#ifndef SANGUIS_COLLISION_OPTIONAL_RESULT_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_OPTIONAL_RESULT_PAIR_FWD_HPP_INCLUDED

#include <sanguis/collision/result_pair_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::collision
{

using
optional_result_pair
=
fcppt::optional::object<
	sanguis::collision::result_pair
>;

}

#endif
