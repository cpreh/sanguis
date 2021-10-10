#include <sanguis/client/log_location.hpp>
#include <sanguis/client/draw2d/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>

fcppt::log::location sanguis::client::draw2d::log_location()
{
  return sanguis::client::log_location() / fcppt::log::name{FCPPT_TEXT("draw2d")};
}
