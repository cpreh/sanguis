#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/gui/hud/weapon_tooltip_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::client::gui::hud
{

using
weapon_tooltip_unique_ptr
=
fcppt::unique_ptr<
	sanguis::client::gui::hud::weapon_tooltip
>;

}

#endif
