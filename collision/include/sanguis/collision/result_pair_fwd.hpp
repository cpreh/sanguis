#ifndef SANGUIS_COLLISION_RESULT_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_RESULT_PAIR_FWD_HPP_INCLUDED

#include <sanguis/collision/result_fwd.hpp>
#include <fcppt/homogenous_pair_fwd.hpp>


namespace sanguis
{
namespace collision
{

typedef
fcppt::homogenous_pair<
	sanguis::collision::result
>
result_pair;

}
}

#endif
