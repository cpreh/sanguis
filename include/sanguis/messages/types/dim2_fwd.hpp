#ifndef SANGUIS_MESSAGES_TYPES_DIM2_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_DIM2_FWD_HPP_INCLUDED

#include <sanguis/messages/types/size.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sanguis
{
namespace messages
{
namespace types
{

typedef fcppt::math::dim::static_<
	sanguis::messages::types::size,
	2u
> dim2;

}
}
}

#endif
