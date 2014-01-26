#ifndef SANGUIS_CLIENT_TO_GUI_DURATION_HPP_INCLUDED
#define SANGUIS_CLIENT_TO_GUI_DURATION_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/gui/duration.hpp>


namespace sanguis
{
namespace client
{

sanguis::gui::duration
to_gui_duration(
	sanguis::duration const &
);

}
}

#endif
