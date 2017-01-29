#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type_to_is_primary.hpp>
#include <sanguis/client/weapon_pair.hpp>


sanguis::client::weapon_pair::weapon_pair()
:
	primary_(),
	secondary_()
{
}

void
sanguis::client::weapon_pair::add(
	sanguis::weapon_description const &_description
)
{
	this->get(
		sanguis::weapon_type_to_is_primary(
			_description.weapon_type()
		)
	) =
		sanguis::optional_weapon_description(
			_description
		);
}

void
sanguis::client::weapon_pair::remove(
	sanguis::is_primary_weapon const _is_primary
)
{
	this->get(
		_is_primary
	) =
		sanguis::optional_weapon_description();
}

sanguis::optional_weapon_description const &
sanguis::client::weapon_pair::get(
	sanguis::is_primary_weapon const _is_primary
) const
{
	return
		_is_primary.get()
		?
			primary_
		:
			secondary_
		;
}

sanguis::optional_weapon_description &
sanguis::client::weapon_pair::get(
	sanguis::is_primary_weapon const _is_primary
)
{
	return
		_is_primary.get()
		?
			primary_
		:
			secondary_
		;
}
