#ifndef SANGUIS_CLIENT_GUI_PERK_MAKE_TABS_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_MAKE_TABS_HPP_INCLUDED

#include <sanguis/client/gui/perk/tab_unique_ptr_vector.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/renderer/device/ffp_ref.hpp>

namespace sanguis::client::gui::perk
{

sanguis::client::gui::perk::tab_unique_ptr_vector make_tabs(
    sge::renderer::device::ffp_ref,
    sge::font::object_ref,
    sge::gui::context_ref,
    sge::gui::style::const_reference,
    sanguis::client::perk::state_ref);

}

#endif
