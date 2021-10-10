#ifndef SANGUIS_CLIENT_CONTROL_ENVIRONMENT_CREF_HPP_INCLUDED
#define SANGUIS_CLIENT_CONTROL_ENVIRONMENT_CREF_HPP_INCLUDED

#include <sanguis/client/control/environment_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::client::control
{

using environment_cref = fcppt::reference<sanguis::client::control::environment const>;

}

#endif
