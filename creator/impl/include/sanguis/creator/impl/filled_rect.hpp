#ifndef SANGUIS_CREATOR_IMPL_FILLED_RECT_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_FILLED_RECT_HPP_INCLUDED

#include <sanguis/creator/rect.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/container/grid/make_min.hpp>
#include <fcppt/container/grid/make_pos_range_start_end.hpp>
#include <fcppt/container/grid/make_sup.hpp>

namespace sanguis::creator::impl
{

template <typename Callback>
void filled_rect(sanguis::creator::rect const &_rect, Callback const &_callback)
{
  fcppt::algorithm::loop(
      fcppt::container::grid::make_pos_range_start_end(
          fcppt::container::grid::make_min(_rect.pos()),
          fcppt::container::grid::make_sup(_rect.max())),
      _callback);
}

}

#endif
