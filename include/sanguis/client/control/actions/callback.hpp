#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_CALLBACK_HPP_INCLUDED

#include <sanguis/client/control/actions/any_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace control
{
namespace actions
{

typedef std::function<
	void (
		sanguis::client::control::actions::any const &
	)
> callback;

}
}
}
}

#endif
