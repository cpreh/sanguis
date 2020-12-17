#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_SIZE_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/unsigned_fwd.hpp>
#include <sanguis/messages/types/size.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

using
size
=
sanguis::messages::adapted_types::unsigned_<
	sanguis::messages::types::size
>;

}
}
}

#endif
