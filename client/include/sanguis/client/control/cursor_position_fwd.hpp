#ifndef SANGUIS_CLIENT_CONTROL_CURSOR_POSITION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_CURSOR_POSITION_FWD_HPP_INCLUDED

#include <sanguis/client/control/cursor_unit.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

using
cursor_position
=
fcppt::math::vector::static_<
	sanguis::client::control::cursor_unit,
	2
>;

}
}
}

#endif
