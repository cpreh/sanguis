#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part_fwd.hpp>
#include <sanguis/model/part_map.hpp>
#include <sanguis/model/part_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::model::object::object(
    sanguis::model::cell_size const _cell_size,
    sanguis::model::optional_animation_delay const _animation_delay,
    sanguis::model::part_map &&_parts,
    sanguis::model::optional_image_name &&_image_name)
    : cell_size_{_cell_size},
      animation_delay_{_animation_delay},
      parts_(std::move(_parts)),
      image_name_{std::move(_image_name)}
{
}

sanguis::model::object::object(object &&) noexcept = default;

sanguis::model::object &sanguis::model::object::operator=(object &&) noexcept = default;

sanguis::model::object::~object() = default;

sanguis::model::optional_animation_delay sanguis::model::object::animation_delay() const
{
  return animation_delay_;
}

void sanguis::model::object::animation_delay(
    sanguis::model::optional_animation_delay const _animation_delay)
{
  animation_delay_ = _animation_delay;
}

sanguis::model::part &sanguis::model::object::part(sanguis::model::part_name const &_name)
{
  return fcppt::optional::to_exception(
             fcppt::container::find_opt_mapped(parts_, _name),
             [_name]
             { return sanguis::model::exception{FCPPT_TEXT("No part named ") + _name.get()}; })
      .get();
}

sanguis::model::part const &
sanguis::model::object::part(sanguis::model::part_name const &_name) const
{
  return const_cast<sanguis::model::object &>(*this).part(_name);
}

sanguis::model::part &sanguis::model::object::operator[](sanguis::model::part_name const &_name)
{
  return parts_[_name];
}

sanguis::model::part_map &sanguis::model::object::parts() { return parts_; }

sanguis::model::part_map const &sanguis::model::object::parts() const { return parts_; }

sanguis::model::cell_size sanguis::model::object::cell_size() const { return cell_size_; }

sanguis::model::optional_image_name const &sanguis::model::object::image_name() const
{
  return image_name_;
}
