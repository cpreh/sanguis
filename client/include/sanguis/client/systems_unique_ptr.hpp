#ifndef SANGUIS_CLIENT_SYSTEMS_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_SYSTEMS_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/systems_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client
{

using systems_unique_ptr = fcppt::unique_ptr<sanguis::client::systems>;

}

#endif
