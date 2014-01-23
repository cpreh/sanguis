#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/messages/convert/to_weapon_attribute_vector.hpp>
#include <sanguis/messages/server/types/weapon_attribute.hpp>
#include <sanguis/messages/server/types/weapon_attribute_vector.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::messages::server::types::weapon_attribute_vector
sanguis::messages::convert::to_weapon_attribute_vector(
	sanguis::weapon_attribute_vector const &_attributes
)
{
	return
		fcppt::algorithm::map<
			sanguis::messages::server::types::weapon_attribute_vector
		>(
			_attributes,
			[](
				sanguis::weapon_attribute const &_attribute
			)
			{
				return
					sanguis::messages::server::types::weapon_attribute(
						_attribute.type(),
						_attribute.base().get(),
						_attribute.extra().get()
					);
			}
		);
}
