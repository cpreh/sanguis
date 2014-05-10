#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/messages/convert/to_weapon_attribute_vector.hpp>
#include <sanguis/messages/roles/weapon_attribute_base.hpp>
#include <sanguis/messages/roles/weapon_attribute_extra.hpp>
#include <sanguis/messages/roles/weapon_attribute_type.hpp>
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
						sanguis::messages::roles::weapon_attribute_type{} =
							_attribute.type(),
						sanguis::messages::roles::weapon_attribute_base{} =
							_attribute.base().get(),
						sanguis::messages::roles::weapon_attribute_extra{} =
							_attribute.extra().get()
					);
			}
		);
}
