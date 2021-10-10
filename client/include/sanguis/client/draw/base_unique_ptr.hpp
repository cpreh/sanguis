#ifndef SANGUIS_CLIENT_DRAW_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/draw/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client::draw
{

using base_unique_ptr = fcppt::unique_ptr<sanguis::client::draw::base>;

}

#endif
