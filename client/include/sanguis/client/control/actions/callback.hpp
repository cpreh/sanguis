#ifndef SANGUIS_CLIENT_CONTROL_ACTIONS_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ACTIONS_CALLBACK_HPP_INCLUDED

#include <sanguis/client/control/actions/any_fwd.hpp>
#include <fcppt/function_impl.hpp>

namespace sanguis::client::control::actions
{

using callback = fcppt::function<void(sanguis::client::control::actions::any const &)>;

}

#endif
