#ifndef SANGUIS_COLLISION_RESULT_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_RESULT_PAIR_FWD_HPP_INCLUDED

#include <sanguis/collision/result_fwd.hpp>
#include <fcppt/tuple/object_fwd.hpp>


namespace sanguis
{
namespace collision
{

using
result_pair
=
fcppt::tuple::object<
	sanguis::collision::result,
	sanguis::collision::result
>;

}
}

#endif
