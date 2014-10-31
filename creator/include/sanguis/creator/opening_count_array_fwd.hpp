#ifndef SANGUIS_CREATOR_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_OPENING_COUNT_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/creator/opening_count_fwd.hpp>
#include <sanguis/creator/opening_type_fwd.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::enum_array<
	sanguis::creator::opening_type,
	sanguis::creator::opening_count
>
opening_count_array;

}
}

#endif
