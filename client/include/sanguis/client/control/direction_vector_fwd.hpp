#ifndef SANGUIS_CLIENT_CONTROL_DIRECTION_VECTOR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_DIRECTION_VECTOR_FWD_HPP_INCLUDED

#include <sanguis/client/control/scalar.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

using
direction_vector
=
fcppt::math::vector::static_<
	sanguis::client::control::scalar,
	2
>;

}
}
}

#endif
