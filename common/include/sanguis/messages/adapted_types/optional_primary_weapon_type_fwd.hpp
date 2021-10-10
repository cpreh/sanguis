#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_OPTIONAL_PRIMARY_WEAPON_TYPE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_OPTIONAL_PRIMARY_WEAPON_TYPE_FWD_HPP_INCLUDED

#include <sanguis/primary_weapon_type_fwd.hpp>
#include <sanguis/messages/adapted_types/primary_weapon_type_fwd.hpp>
#include <alda/bindings/optional_decl.hpp>

namespace sanguis::messages::adapted_types
{

using optional_primary_weapon_type = alda::bindings::
    optional<sanguis::primary_weapon_type, sanguis::messages::adapted_types::primary_weapon_type>;

}

#endif
