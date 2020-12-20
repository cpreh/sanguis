#ifndef SANGUIS_CLIENT_ARGS_ELEMENTS_DISPLAY_HEIGHT_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_ARGS_ELEMENTS_DISPLAY_HEIGHT_FWD_HPP_INCLUDED

#include <sanguis/client/args/optional_screen_unit_fwd.hpp>
#include <sanguis/client/args/labels/display_height.hpp>
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
display_height
=
fcppt::record::element<
	sanguis::client::args::labels::display_height,
	sanguis::client::args::optional_screen_unit
>;

}
}
}
}

#endif
