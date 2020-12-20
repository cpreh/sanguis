#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_VARIANT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_VARIANT_FWD_HPP_INCLUDED

#include <sanguis/client/control/actions/binary_fwd.hpp>
#include <sanguis/client/control/actions/cursor_fwd.hpp>
#include <sanguis/client/control/actions/nullary_fwd.hpp>
#include <sanguis/client/control/actions/scale_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

using
variant
=
fcppt::variant::object<
	sanguis::client::control::actions::binary,
	sanguis::client::control::actions::cursor,
	sanguis::client::control::actions::nullary,
	sanguis::client::control::actions::scale
>;

}
}
}
}

#endif
