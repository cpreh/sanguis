#ifndef SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/optional_weapon_attribute_value_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_attribute_type_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_attribute_value_fwd.hpp>
#include <sanguis/messages/roles/weapon_attribute_base.hpp>
#include <sanguis/messages/roles/weapon_attribute_extra.hpp>
#include <sanguis/messages/roles/weapon_attribute_type.hpp>
#include <alda/raw/record_variadic_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace types
{

typedef
alda::raw::record_variadic<
	fcppt::record::element<
		sanguis::messages::roles::weapon_attribute_type,
		sanguis::messages::adapted_types::weapon_attribute_type
	>,
	fcppt::record::element<
		sanguis::messages::roles::weapon_attribute_base,
		sanguis::messages::adapted_types::weapon_attribute_value
	>,
	fcppt::record::element<
		sanguis::messages::roles::weapon_attribute_extra,
		sanguis::messages::adapted_types::optional_weapon_attribute_value
	>
>
weapon_attribute;

}
}
}
}

#endif
