#ifndef SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_WEAPON_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_PARTS_ADD_WITH_WEAPON_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/messages/adapted_types/weapon_status_fwd.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element_fwd.hpp>

namespace sanguis::messages::server::parts
{

using add_with_weapon = fcppt::mpl::list::object<
    fcppt::record::element<
        sanguis::messages::roles::primary_weapon,
        sanguis::messages::adapted_types::optional_primary_weapon_type>,
    fcppt::record::element<
        sanguis::messages::roles::weapon_status,
        sanguis::messages::adapted_types::weapon_status>>;

}

#endif
