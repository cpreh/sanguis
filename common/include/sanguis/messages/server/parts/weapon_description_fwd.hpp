#ifndef SANGUIS_MESSAGES_SERVER_PARTS_WEAPON_DESCRIPTION_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_WEAPON_DESCRIPTION_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/duration_fwd.hpp>
#include <sanguis/messages/adapted_types/magazine_size_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_type_fwd.hpp>
#include <sanguis/messages/roles/magazine_base_size.hpp>
#include <sanguis/messages/roles/magazine_extra_size.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/roles/reload_time.hpp>
#include <sanguis/messages/roles/weapon_attribute_container.hpp>
#include <sanguis/messages/roles/weapon_type.hpp>
#include <sanguis/messages/server/adapted_types/weapon_attribute_vector_fwd.hpp>
#include <fcppt/record/element_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace messages
{
namespace server
{
namespace parts
{

typedef
metal::list<
	fcppt::record::element<
		sanguis::messages::roles::weapon_type,
		sanguis::messages::adapted_types::weapon_type
	>,
	fcppt::record::element<
		sanguis::messages::roles::magazine_base_size,
		sanguis::messages::adapted_types::magazine_size
	>,
	fcppt::record::element<
		sanguis::messages::roles::magazine_extra_size,
		sanguis::messages::adapted_types::magazine_size
	>,
	fcppt::record::element<
		sanguis::messages::roles::magazine_remaining,
		sanguis::messages::adapted_types::magazine_size
	>,
	fcppt::record::element<
		sanguis::messages::roles::reload_time,
		sanguis::messages::adapted_types::duration
	>,
	fcppt::record::element<
		sanguis::messages::roles::weapon_attribute_container,
		sanguis::messages::server::adapted_types::weapon_attribute_vector
	>
>
weapon_description;

}
}
}
}

#endif
