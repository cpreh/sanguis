#ifndef SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_SERVER_TYPES_WEAPON_ATTRIBUTE_FWD_HPP_INCLUDED

#include <sanguis/messages/server/adapted_types/weapon_attribute_fwd.hpp>
#include <alda/bindings/float_decl.hpp> // IWYU pragma: keep
#include <alda/bindings/optional_decl.hpp> // IWYU pragma: keep
#include <alda/bindings/record_variadic_decl.hpp> // IWYU pragma: keep
#include <alda/bindings/strong_typedef_decl.hpp> // IWYU pragma: keep
#include <alda/raw/element_type.hpp>

namespace sanguis::messages::server::types
{

using weapon_attribute =
    alda::raw::element_type<sanguis::messages::server::adapted_types::weapon_attribute>;

}

#endif
