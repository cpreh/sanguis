#ifndef SANGUIS_SERVER_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/math/vector/static_fwd.hpp>

namespace sanguis::server
{

using vector = fcppt::math::vector::static_<sanguis::server::space_unit, 2>;

}

#endif
