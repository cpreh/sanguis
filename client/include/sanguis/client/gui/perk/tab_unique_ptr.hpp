#ifndef SANGUIS_CLIENT_GUI_PERK_TAB_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_TAB_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/gui/perk/tab_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sanguis::client::gui::perk
{

using tab_unique_ptr = fcppt::unique_ptr<sanguis::client::gui::perk::tab>;

}

#endif
