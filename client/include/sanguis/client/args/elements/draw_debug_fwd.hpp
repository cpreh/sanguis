#ifndef SANGUIS_CLIENT_ARGS_ELEMENTS_DRAW_DEBUG_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_ELEMENTS_DRAW_DEBUG_FWD_HPP_INCLUDED

#include <sanguis/client/args/labels/draw_debug.hpp>
#include <sanguis/client/draw/debug.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace args
{
namespace elements
{

using
draw_debug
=
fcppt::record::element<
	sanguis::client::args::labels::draw_debug,
	sanguis::client::draw::debug
>;

}
}
}
}

#endif
