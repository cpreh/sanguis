#include <sanguis/log_location.hpp>
#include <sanguis/tiles/log_location.hpp>
#include <sanguis/tiles/impl/log_name.hpp>
#include <fcppt/log/location.hpp>

fcppt::log::location sanguis::tiles::log_location()
{
  return sanguis::log_location() / sanguis::tiles::impl::log_name();
}
