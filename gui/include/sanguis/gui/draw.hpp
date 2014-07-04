#ifndef SANGUIS_GUI_DRAW_HPP_INCLUDED
#define SANGUIS_GUI_DRAW_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/background/base_fwd.hpp>
#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>


namespace sanguis
{
namespace gui
{

SANGUIS_GUI_SYMBOL
void
draw(
	sge::renderer::context::ffp &,
	sanguis::gui::background::base &,
	sanguis::gui::main_area::base &
);

}
}

#endif
