#ifndef SANGUIS_CREATOR_OPENING_CONTAINER_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_OPENING_CONTAINER_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_type_fwd.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::enum_array<
	sanguis::creator::opening_type,
	sanguis::creator::opening_container
>
opening_container_array;

}
}

#endif
