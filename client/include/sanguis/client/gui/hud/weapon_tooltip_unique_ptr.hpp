#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_TOOLTIP_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/gui/hud/weapon_tooltip_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

typedef
std::unique_ptr<
	sanguis::client::gui::hud::weapon_tooltip
>
weapon_tooltip_unique_ptr;

}
}
}
}

#endif
