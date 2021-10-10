#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/animation_range.hpp>
#include <sanguis/model/cell_area.hpp>
#include <sanguis/model/cell_area_container.hpp>
#include <sanguis/model/cell_area_from_index.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/image_size.hpp>
#include <sanguis/model/make_cell_areas.hpp>
#include <fcppt/make_int_range.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/math/box/contains.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/null.hpp>

sanguis::model::cell_area_container sanguis::model::make_cell_areas(
    sanguis::model::image_size const &_image_size,
    sanguis::model::cell_size const &_cell_size,
    sanguis::model::animation_range const _range)
{
  if (_range.begin() >= _range.end())
  {
    throw sanguis::model::exception{
        FCPPT_TEXT("begin/end invalid: begin = ") + fcppt::output_to_fcppt_string(_range.begin()) +
        FCPPT_TEXT(", end = ") + fcppt::output_to_fcppt_string(_range.end())};
  }

  return fcppt::algorithm::map<sanguis::model::cell_area_container>(
      fcppt::make_int_range(_range.begin(), _range.end()),
      [_image_size, _cell_size](sanguis::model::animation_index const _index)
      {
        sanguis::model::cell_area cur_area(
            sanguis::model::cell_area_from_index(_image_size, _cell_size, _index));

        if (!fcppt::math::box::contains(
                sanguis::model::cell_area(
                    fcppt::math::vector::null<sanguis::model::cell_area::vector>(),
                    _image_size.get()),
                cur_area))
        {
          throw sanguis::model::exception{
              FCPPT_TEXT("Rect out of bounds. Image size is ") +
              fcppt::output_to_fcppt_string(_image_size) + FCPPT_TEXT(" but the inner area is ") +
              fcppt::output_to_fcppt_string(cur_area)};
        }

        return cur_area;
      });
}
