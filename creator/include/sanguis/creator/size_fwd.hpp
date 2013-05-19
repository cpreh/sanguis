#ifndef SANGUIS_CREATOR_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_SIZE_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sanguis
{
namespace creator
{

typedef fcppt::math::dim::static_<
	sanguis::creator::size_type,
	2
>::type size;

}
}

#endif
