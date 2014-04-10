#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_base.hpp>
#include <sanguis/weapon_attribute_extra.hpp>
#include <sanguis/weapon_attribute_vector.hpp>
#include <sanguis/messages/adapted_types/weapon_attribute_type.hpp>
#include <sanguis/messages/convert/from_weapon_attribute_vector.hpp>
#include <sanguis/messages/roles/weapon_attribute_base.hpp>
#include <sanguis/messages/roles/weapon_attribute_extra.hpp>
#include <sanguis/messages/server/types/weapon_attribute.hpp>
#include <sanguis/messages/server/types/weapon_attribute_vector.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::weapon_attribute_vector
sanguis::messages::convert::from_weapon_attribute_vector(
	sanguis::messages::server::types::weapon_attribute_vector const &_attributes
)
{
	return
		fcppt::algorithm::map<
			sanguis::weapon_attribute_vector
		>(
			_attributes,
			[](
				sanguis::messages::server::types::weapon_attribute const &_attribute
			)
			{
				return
					sanguis::weapon_attribute(
						_attribute.get<
							sanguis::messages::adapted_types::weapon_attribute_type
						>(),
						sanguis::weapon_attribute_base(
							_attribute.get<
								sanguis::messages::roles::weapon_attribute_base
							>()
						),
						sanguis::weapon_attribute_extra(
							_attribute.get<
								sanguis::messages::roles::weapon_attribute_extra
							>()
						)
					);
			}
		);
}
