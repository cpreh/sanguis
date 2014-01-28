#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>


sge::image::color::any::object const
sanguis::client::gui::hud::weapon_attribute_color(
	sanguis::weapon_attribute_type const _type
)
{
	// TODO
	return
		sge::image::color::predef::black();
}
