#include <sanguis/model/animation_index.hpp>
#include <sanguis/model/animation_range.hpp>

sanguis::model::animation_range::animation_range(
    sanguis::model::animation_index const _begin, sanguis::model::animation_index const _end)
    : begin_(_begin), end_(_end)
{
}

sanguis::model::animation_index sanguis::model::animation_range::begin() const { return begin_; }

sanguis::model::animation_index sanguis::model::animation_range::end() const { return end_; }
