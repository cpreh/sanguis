#ifndef SANGUIS_CLIENT_GUI_PERK_MAKE_TABS_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_MAKE_TABS_HPP_INCLUDED

#include <sanguis/client/gui/perk/tab_unique_ptr_vector.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

sanguis::client::gui::perk::tab_unique_ptr_vector
make_tabs(
	sge::renderer::device::ffp &,
	sge::font::object &,
	sanguis::gui::context &,
	sanguis::gui::style::base const &,
	sanguis::client::perk::state &
);

}
}
}
}

#endif
