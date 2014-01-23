#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_HPP_INCLUDED

#include <sanguis/optional_weapon_attribute_value.hpp>
#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_type.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace attributes
{

template<
	typename Attribute
>
sanguis::weapon_attribute
make(
	sanguis::weapon_attribute_type const _type,
	Attribute const &_attribute
)
{
	return
		sanguis::weapon_attribute(
			_type,
			sanguis::weapon_attribute_base(
				_attribute.base().get()
			),
			sanguis::weapon_attribute_extra(
				_attribute.extra()
				?
					sanguis::optional_weapon_attribute_value(
						_attribute.extra()->get()
					)
				:
					sanguis::optional_weapon_attribute_value()
			)
		);
}

}
}
}
}

#endif
