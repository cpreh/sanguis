#ifndef SANGUIS_MESSAGES_TYPES_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_MESSAGES_TYPES_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/creator/opening_type_fwd.hpp>
#include <sanguis/messages/types/size.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


namespace sanguis
{
namespace messages
{
namespace types
{

typedef
fcppt::container::enum_array<
	sanguis::creator::opening_type,
	sanguis::messages::types::size
>
opening_count_array;

}
}
}

#endif
