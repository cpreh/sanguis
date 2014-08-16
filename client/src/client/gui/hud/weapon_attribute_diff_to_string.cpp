#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_diff_to_string.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_value_to_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>


sge::font::string
sanguis::client::gui::hud::weapon_attribute_diff_to_string(
	sanguis::weapon_attribute_value const _value
)
{
	sge::font::string result;

	if(
		_value
		>
		0
	)
		result +=
			SGE_FONT_LIT('+');

	return
		result
		+=
		sanguis::client::gui::hud::weapon_attribute_value_to_string(
			_value
		);
}
