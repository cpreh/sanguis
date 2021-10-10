#ifndef SANGUIS_CLIENT_CURSOR_REF_HPP_INCLUDED
#define SANGUIS_CLIENT_CURSOR_REF_HPP_INCLUDED

#include <sanguis/client/cursor_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis::client
{

using cursor_ref = fcppt::reference<sanguis::client::cursor>;

}

#endif
