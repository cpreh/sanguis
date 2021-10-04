#ifndef SANGUIS_CLIENT_GUI_TO_DURATION_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_TO_DURATION_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sge/gui/duration.hpp>


namespace sanguis::client::gui
{

sge::gui::duration
to_duration(
	sanguis::duration const &
);

}

#endif
