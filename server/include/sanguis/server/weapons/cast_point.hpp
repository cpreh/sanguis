#ifndef SANGUIS_SERVER_WEAPONS_CAST_POINT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CAST_POINT_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::weapons
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::duration, cast_point);

}

#endif
