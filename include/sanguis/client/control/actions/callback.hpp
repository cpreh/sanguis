#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_CALLBACK_HPP_INCLUDED

#include <sanguis/client/control/actions/any_fwd.hpp>
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

typedef fcppt::function::object<
	void (
		actions::any const &
	)
> callback;

}
}
}
}

#endif
