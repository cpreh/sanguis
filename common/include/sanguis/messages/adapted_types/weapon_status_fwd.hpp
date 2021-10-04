#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_STATUS_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_WEAPON_STATUS_FWD_HPP_INCLUDED

#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/messages/adapted_types/enum_fwd.hpp>


namespace sanguis::messages::adapted_types
{

using
weapon_status
=
sanguis::messages::adapted_types::enum_<
	sanguis::weapon_status
>;

}

#endif
