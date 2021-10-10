#include <sanguis/client/draw2d/log_location.hpp>
#include <sanguis/client/draw2d/scene/log_name.hpp>
#include <sanguis/client/draw2d/scene/world/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>

fcppt::log::location sanguis::client::draw2d::scene::world::log_location()
{
  return sanguis::client::draw2d::log_location() / sanguis::client::draw2d::scene::log_name() /
         fcppt::log::name{FCPPT_TEXT("world")};
}
