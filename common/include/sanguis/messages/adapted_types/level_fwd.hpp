#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_LEVEL_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_LEVEL_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/unsigned_fwd.hpp>
#include <sanguis/messages/types/level.hpp>


namespace sanguis::messages::adapted_types
{

using
level
=
sanguis::messages::adapted_types::unsigned_<
	sanguis::messages::types::level
>;

}

#endif
