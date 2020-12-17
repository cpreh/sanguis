#ifndef SANGUIS_MESSAGES_TYPES_VECTOR2_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_VECTOR2_FWD_HPP_INCLUDED

#include <sanguis/messages/types/space_unit.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace types
{

using
vector2
=
fcppt::math::vector::static_<
	sanguis::messages::types::space_unit,
	2U
>;

}
}
}

#endif
