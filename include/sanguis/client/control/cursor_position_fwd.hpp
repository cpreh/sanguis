#ifndef SANGUIS_CLIENT_CONTROL_CURSOR_POSITION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_CURSOR_POSITION_FWD_HPP_INCLUDED

#include <sanguis/client/control/cursor_unit.hpp>
#include <fcppt/math/vector/static.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

typedef fcppt::math::vector::static_<
	sanguis::client::control::cursor_unit,
	2
>::type cursor_position;

}
}
}

#endif
