#include <sanguis/exception.hpp>
#include <sanguis/client/draw2d/entities/buffs/base.hpp>
#include <sanguis/client/draw2d/entities/model/object_fwd.hpp>
#include <fcppt/text.hpp>

sanguis::client::draw2d::entities::buffs::base::base() : counter_(1U) {}

sanguis::client::draw2d::entities::buffs::base::~base() = default;

void sanguis::client::draw2d::entities::buffs::base::apply(
    sanguis::client::draw2d::entities::model::object &)
{
}

void sanguis::client::draw2d::entities::buffs::base::remove(
    sanguis::client::draw2d::entities::model::object &)
{
}

void sanguis::client::draw2d::entities::buffs::base::update(
    sanguis::client::draw2d::entities::model::object const &)
{
}

void sanguis::client::draw2d::entities::buffs::base::increment() { ++counter_; }

bool sanguis::client::draw2d::entities::buffs::base::decrement()
{
  if (counter_ == 0U)
  {
    throw sanguis::exception{FCPPT_TEXT("Invalid decrement in buffs::base!")};
  }

  return --counter_ == 0U;
}
