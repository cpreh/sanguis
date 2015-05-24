#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/gui/hud/weapon_tooltip_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

typedef
fcppt::unique_ptr<
	sanguis::client::gui::hud::weapon_tooltip
>
weapon_tooltip_unique_ptr;

}
}
}
}

#endif
