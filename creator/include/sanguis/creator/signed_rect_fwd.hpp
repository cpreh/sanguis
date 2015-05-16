#ifndef SANGUIS_CREATOR_SIGNED_RECT_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_SIGNED_RECT_FWD_HPP_INCLUDED

#include <sanguis/creator/difference_type.hpp>
#include <fcppt/math/box/rect_fwd.hpp>

namespace sanguis
{
namespace creator
{

typedef fcppt::math::box::rect<
	sanguis::creator::difference_type
>
signed_rect;

}
}

#endif

