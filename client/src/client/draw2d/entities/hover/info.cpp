#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/variant.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::client::draw2d::entities::hover::info::info(
    sanguis::client::draw2d::entities::hover::variant &&_impl)
    : impl_{std::move(_impl)}
{
}

sanguis::client::draw2d::entities::hover::variant const &
sanguis::client::draw2d::entities::hover::info::get() const
{
  return impl_;
}
