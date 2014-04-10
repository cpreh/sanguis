#include <sanguis/weapon_type.hpp>
#include <sanguis/client/gui/hud/weapon_name.hpp>
#include <sanguis/client/gui/hud/weapon_name_visitor.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <sge/font/string.hpp>


sge::font::string
sanguis::client::gui::hud::weapon_name(
	sanguis::weapon_type const &_weapon_type
)
{
	return
		fcppt::variant::apply_unary(
			sanguis::client::gui::hud::weapon_name_visitor(),
			_weapon_type
		);
}
