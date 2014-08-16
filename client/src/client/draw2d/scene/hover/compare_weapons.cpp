#include <sanguis/optional_weapon_attribute_value.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/client/weapon_attribute_total.hpp>
#include <sanguis/client/weapon_pair.hpp>
#include <sanguis/client/draw2d/scene/hover/compare_weapons.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_diff.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/variant/not_equal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::scene::hover::weapon_attribute_diff const
sanguis::client::draw2d::scene::hover::compare_weapons(
	sanguis::weapon_type const _type,
	sanguis::weapon_attribute const &_attribute,
	sanguis::client::weapon_pair const &_player_weapons
)
{
	sanguis::optional_weapon_description const &desc(
		_player_weapons.get(
			sanguis::weapon_type_to_is_primary(
				_type
			)
		)
	);

	if(
		!desc
		||
		desc->weapon_type()
		!=
		_type
	)
		return
			sanguis::client::draw2d::scene::hover::weapon_attribute_diff(
				sanguis::optional_weapon_attribute_value()
			);

	fcppt::optional<
		sanguis::weapon_attribute
	> const same_attribute(
		fcppt::algorithm::find_if_opt(
			desc->attributes(),
			[
				&_attribute
			](
				sanguis::weapon_attribute const &_comp
			)
			{
				return
					_comp.type()
					==
					_attribute.type();
			}
		)
	);

	if(
		!same_attribute
	)
		return
			sanguis::client::draw2d::scene::hover::weapon_attribute_diff(
				sanguis::optional_weapon_attribute_value()
			);

	auto const whole_value(
		[](
			sanguis::weapon_attribute const &_nattribute
		)
		{
			return
				sanguis::client::weapon_attribute_total(
					_nattribute.base(),
					_nattribute.extra()
				);
		}
	);

	sanguis::weapon_attribute_value const diff(
		whole_value(
			_attribute
		)
		-
		whole_value(
			*same_attribute
		)
	);

	return
		sanguis::client::draw2d::scene::hover::weapon_attribute_diff(
			std::abs(
				diff
			)
			<
			fcppt::literal<
				sanguis::weapon_attribute_value
			>(
				0.01
			)
			?
				sanguis::optional_weapon_attribute_value()
			:
				sanguis::optional_weapon_attribute_value(
					diff
				)
		);
}
