#ifndef SANGUIS_CLIENT_CONTROL_ATTACK_DEST_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ATTACK_DEST_FWD_HPP_INCLUDED

#include <sanguis/client/control/scalar.hpp>
#include <fcppt/math/vector/static.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

typedef fcppt::math::vector::static_<
	sanguis::client::control::scalar,
	2
>::type attack_dest;

}
}
}

#endif