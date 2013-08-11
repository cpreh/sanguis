#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_description.hpp>


sanguis::weapon_description::weapon_description(
	sanguis::string_vector const &_text
)
:
	text_(
		_text
	)
{
}

sanguis::string_vector const &
sanguis::weapon_description::text() const
{
	return text_;
}
