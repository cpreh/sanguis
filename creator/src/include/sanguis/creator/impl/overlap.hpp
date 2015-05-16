#ifndef SANGUIS_CREATOR_IMPL_OVERLAP_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_OVERLAP_HPP_INCLUDED

#include <sanguis/creator/signed_rect_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace impl
{

bool
overlap(
	sanguis::creator::signed_rect const &,
	sanguis::creator::signed_rect const &
);

}
}
}

#endif

