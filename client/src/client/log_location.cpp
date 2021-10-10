#include <sanguis/log_location.hpp>
#include <sanguis/client/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>

fcppt::log::location sanguis::client::log_location()
{
  return sanguis::log_location() / fcppt::log::name{FCPPT_TEXT("client")};
}
