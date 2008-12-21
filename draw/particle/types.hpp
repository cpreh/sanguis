#ifndef SANGUIS_DRAW_PARTICLE_TYPES_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_TYPES_HPP_INCLUDED

#include "../funit.hpp"
#include <sge/random/inclusive_range.hpp>
#include <sge/math/vector.hpp>
#include <sge/sprite/types.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>
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
typedef sge::math::vector<funit, 2>              point;
typedef sge::random::inclusive_range<funit>      dispersion_range;
typedef sge::random::inclusive_range<funit>      velocity_range;
typedef sge::random::inclusive_range<rotation>   rotation_velocity_range;
typedef sge::random::inclusive_range<time_type>  fade_time_range;
typedef boost::optional<fade_time_range>         fade_type;
typedef boost::function<base_ptr ()>             generation_callback;

}
}
}

#endif
