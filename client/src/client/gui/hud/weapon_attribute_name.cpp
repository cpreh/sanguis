#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_name.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>


sge::font::string
sanguis::client::gui::hud::weapon_attribute_name(
	sanguis::weapon_attribute_type const _type
)
{
	#define SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(\
		name\
	)\
	case sanguis::weapon_attribute_type::name:\
		return \
			SGE_FONT_LIT(#name)

	switch(
		_type
	)
	{
		SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(
			accuracy
		);

		SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(
			aoe
		);

		SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(
			damage
		);

		SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(
			health
		);

		SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(
			shells
		);

		SANGUIS_WEAPON_ATTRIBUTE_NAME_CASE(
			spread_radius
		);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
