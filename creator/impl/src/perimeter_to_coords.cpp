#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/impl/perimeter_to_coords.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>

sanguis::creator::grid::pos sanguis::creator::impl::perimeter_to_coords(
    sanguis::creator::grid::dim const &_dim, unsigned const &_t)
{
  if (_dim.w() <= 2U || _dim.h() <= 2U)
  {
    throw sanguis::creator::exception{FCPPT_TEXT("perimeter_to_coords: dim too small!")};
  }

  auto const w2{_dim.w() - 2U};
  auto const h2{_dim.h() - 2U};

  if (fcppt::not_(_t < 2 * w2 + 2 * h2))
  {
    throw sanguis::creator::exception{FCPPT_TEXT("permieter_to_coords: _t too small!")};
  }

  if (_t < w2)
  {
    return sanguis::creator::grid::pos(_t + 1U, 0U);
  }

  if (_t < w2 + h2)
  {
    return sanguis::creator::grid::pos(w2 + 1U, _t - w2 + 1U);
  }

  if (_t < 2U * w2 + h2)
  {
    return sanguis::creator::grid::pos(w2 - (_t - w2 - h2), h2 + 1U);
  }

  return sanguis::creator::grid::pos(0U, h2 - (_t - 2U * w2 - h2));
}
