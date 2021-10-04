#ifndef SANGUIS_COLLISION_OPTIONAL_RESULT_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_OPTIONAL_RESULT_FWD_HPP_INCLUDED

#include <sanguis/collision/result_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::collision
{

using
optional_result
=
fcppt::optional::object<
	sanguis::collision::result
>;

}

#endif
