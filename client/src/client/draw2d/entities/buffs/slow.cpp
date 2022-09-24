#include <sanguis/exception.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/buffs/slow.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_format.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>

sanguis::client::draw2d::entities::buffs::slow::slow()
    : sanguis::client::draw2d::entities::buffs::base(), previous_color_()
{
}

sanguis::client::draw2d::entities::buffs::slow::~slow() = default;

void sanguis::client::draw2d::entities::buffs::slow::apply(
    sanguis::client::draw2d::entities::model::object &_model)
{
  if (previous_color_.has_value())
  {
    throw sanguis::exception{FCPPT_TEXT("buffs::slow: already applied")};
  }

  previous_color_ = optional_color(_model.color());

  _model.color(sge::image::color::convert<sanguis::client::draw2d::sprite::normal::color_format>(
      sge::image::color::predef::lightblue()));
}

void sanguis::client::draw2d::entities::buffs::slow::remove(
    sanguis::client::draw2d::entities::model::object &_model)
{
  fcppt::optional::maybe_void(
      this->previous_color_,
      [&_model](sanguis::client::draw2d::sprite::normal::color const &_previous_color)
      { _model.color(_previous_color); });

  this->previous_color_ = optional_color();
}
