#ifndef SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_ATTRIBUTES_MAKE_HPP_INCLUDED

#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_type.hpp>
#include <sanguis/server/weapons/attributes/basic_impl.hpp>
#include <fcppt/optional_bind_construct.hpp>


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
	sanguis::server::weapons::attributes::basic<
		Attribute
	> const &_attribute
)
{
	return
		sanguis::weapon_attribute(
			_type,
			sanguis::weapon_attribute_base(
				_attribute.base().get()
			),
			sanguis::weapon_attribute_extra(
				fcppt::optional_bind_construct(
					_attribute.extra(),
					[](
						Attribute const _extra
					)
					{
						return
							_extra.get();
					}
				)
			)
		);
}

}
}
}
}

#endif
