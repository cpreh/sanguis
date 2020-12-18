#ifndef SANGUIS_COLLISION_RESULT_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_RESULT_PAIR_FWD_HPP_INCLUDED

#include <sanguis/collision/result_fwd.hpp>
#include <fcppt/homogenous_pair_fwd.hpp>


namespace sanguis
{
namespace collision
{

using
result_pair
=
fcppt::homogenous_pair<
	sanguis::collision::result
>;

}
}

#endif
