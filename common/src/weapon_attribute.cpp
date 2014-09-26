#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_type.hpp>


sanguis::weapon_attribute::weapon_attribute(
	sanguis::weapon_attribute_type const _type,
	sanguis::weapon_attribute_base const _base,
	sanguis::weapon_attribute_extra const _extra
)
:
	type_(
		_type
	),
	base_(
		_base
	),
	extra_(
		_extra
	)
{
}

sanguis::weapon_attribute_type
sanguis::weapon_attribute::type() const
{
	return
		type_;
}

sanguis::weapon_attribute_base const
sanguis::weapon_attribute::base() const
{
	return
		base_;
}

sanguis::weapon_attribute_extra const
sanguis::weapon_attribute::extra() const
{
	return
		extra_;
}
