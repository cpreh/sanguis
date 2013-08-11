#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type.hpp>


sanguis::weapon_description::weapon_description(
	sanguis::string_vector const &_text,
	sanguis::weapon_type const &_weapon_type
)
:
	text_(
		_text
	),
	weapon_type_(
		_weapon_type
	)
{
}

sanguis::string_vector const &
sanguis::weapon_description::text() const
{
	return text_;
}

sanguis::weapon_type const &
sanguis::weapon_description::weapon_type() const
{
	return weapon_type_;
}
