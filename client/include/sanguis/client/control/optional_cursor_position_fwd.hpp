#ifndef SANGUIS_CLIENT_CONTROL_OPTIONAL_CURSOR_POSITION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_OPTIONAL_CURSOR_POSITION_FWD_HPP_INCLUDED

#include <sanguis/client/control/cursor_position_fwd.hpp>
#include <fcppt/optional_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace control
{

typedef
fcppt::optional<
	sanguis::client::control::cursor_position
>
optional_cursor_position;

}
}
}

#endif
