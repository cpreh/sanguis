#ifndef SANGUIS_SERVER_DIM_TYPE_HPP_INCLUDED
#define SANGUIS_SERVER_DIM_TYPE_HPP_INCLUDED

#include <sge/math/dim/static.hpp>

namespace sanguis
{
namespace server
{

// TODO: is this right?
typedef sge::math::dim::static_<
	unsigned,
	2
>::type dim_type;

}
}

#endif
