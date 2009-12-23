#ifndef SANGUIS_DRAW_PARTICLE_TYPES_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_TYPES_HPP_INCLUDED

// TODO: split this!

#include "base_ptr.hpp"
#include "../funit.hpp"
#include <fcppt/random/inclusive_range.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <sge/optional_fwd.hpp>
#include "fwd.hpp"

namespace sanguis 
{
namespace draw
{
namespace particle
{

typedef funit depth;
typedef funit rotation;
typedef funit time_type;
typedef fcppt::math::vector::static_<funit, 2>::type point;
typedef fcppt::random::inclusive_range<funit>      dispersion_range;
typedef fcppt::random::inclusive_range<funit>      velocity_range;
typedef fcppt::random::inclusive_range<rotation>   rotation_velocity_range;
typedef fcppt::random::inclusive_range<time_type>  fade_time_range;
typedef sge::optional<fade_time_range>         fade_type;
typedef fcppt::function::object<base_ptr ()>             generation_callback;

}
}
}

#endif
