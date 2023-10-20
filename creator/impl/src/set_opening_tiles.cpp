#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/set_opening_tiles.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/strong_typedef_output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/math/vector/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/to_exception.hpp>

void sanguis::creator::impl::set_opening_tiles(
    fcppt::reference<sanguis::creator::grid> const _grid,
    sanguis::creator::opening_container_array const &_openings)
{
  for (sanguis::creator::opening_type const opening_type :
       fcppt::enum_::make_range<sanguis::creator::opening_type>())
  {
    for (sanguis::creator::opening const &opening : _openings[opening_type])
    {
      fcppt::optional::to_exception(
          fcppt::container::grid::at_optional(_grid.get(), opening.get()),
          [&opening]
          {
            return sanguis::creator::exception{
                FCPPT_TEXT("Opening tile ") + fcppt::output_to_fcppt_string(opening) +
                FCPPT_TEXT(" out of range!")};
          })
          .get() = sanguis::creator::tile::stairs;
    }
  }
}
