#ifndef SANGUIS_SERVER_DIM_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_DIM_FWD_HPP_INCLUDED

#include <sanguis/server/space_unit.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sanguis
{
namespace server
{

typedef fcppt::math::dim::static_<
	sanguis::server::space_unit,
	2
> dim;

}
}

#endif
