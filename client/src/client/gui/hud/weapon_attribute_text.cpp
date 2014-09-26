#include <sanguis/weapon_attribute.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_diff_to_string.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_text.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_value_to_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>


sge::font::string
sanguis::client::gui::hud::weapon_attribute_text(
	sanguis::weapon_attribute const &_attribute
)
{
	sge::font::string result(
		sanguis::client::gui::hud::weapon_attribute_value_to_string(
			_attribute.base().get()
		)
	);

	if(
		_attribute.extra().get()
	)
	{
		result +=
			SGE_FONT_LIT(' ');

		result +=
			sanguis::client::gui::hud::weapon_attribute_diff_to_string(
				*_attribute.extra().get()
			);
	}

	return
		result;
}
