#ifndef SANGUIS_CLIENT_CONTROL_DIRECTION_VECTOR_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_DIRECTION_VECTOR_HPP_INCLUDED

#include <sanguis/client/control/scalar.hpp>
#include <fcppt/math/vector/static.hpp>

namespace sanguis
{
namespace client
{
namespace control
{

typedef fcppt::math::vector::static_<
	control::scalar,
	2
>::type direction_vector;

}
}
}

#endif
