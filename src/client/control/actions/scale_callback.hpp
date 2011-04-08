#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_SCALE_CALLBACK_HPP_INCLUDED

#include "scale_fwd.hpp"
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
		actions::scale const &
	)
> scale_callback;

}
}
}
}

#endif
