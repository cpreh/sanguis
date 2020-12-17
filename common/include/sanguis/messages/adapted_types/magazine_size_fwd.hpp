#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_MAGAZINE_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_MAGAZINE_SIZE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/unsigned_fwd.hpp>
#include <sanguis/messages/types/magazine_size.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

using
magazine_size
=
sanguis::messages::adapted_types::unsigned_<
	sanguis::messages::types::magazine_size
>;

}
}
}

#endif
