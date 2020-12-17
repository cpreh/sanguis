#ifndef SANGUIS_MESSAGES_ADAPTED_TYPES_VECTOR2_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_ADAPTED_TYPES_VECTOR2_FWD_HPP_INCLUDED

#include <sanguis/messages/adapted_types/space_unit_fwd.hpp>
#include <sanguis/messages/types/vector2_fwd.hpp>
#include <alda/bindings/static_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace adapted_types
{

using
vector2
=
alda::bindings::static_<
	sanguis::messages::types::vector2,
	sanguis::messages::adapted_types::space_unit
>;

}
}
}

#endif
