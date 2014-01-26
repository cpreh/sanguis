#include <sanguis/weapon_attribute.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_attribute_name.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_attribute_text.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/insert_to_string.hpp>


sge::font::string
sanguis::client::draw2d::scene::hud::weapon_attribute_text(
	sanguis::weapon_attribute const &_attribute
)
{
	sge::font::string result(
		fcppt::insert_to_string<
			sge::font::string
		>(
			_attribute.base()
		)
	);

	if(
		_attribute.extra().get()
	)
	{
		result +=
			SGE_FONT_LIT(' ');

		if(
			*_attribute.extra().get()
			>
			0
		)
			result +=
				SGE_FONT_LIT('+');

		result +=
			fcppt::insert_to_string<
				sge::font::string
			>(
				*_attribute.extra().get()
			);
	}

	return
		result +=
			sanguis::client::draw2d::scene::hud::weapon_attribute_name(
				_attribute.type()
			);
}
