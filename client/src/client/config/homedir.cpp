#include <sanguis/config_app_name.hpp>
#include <sanguis/client/config/homedir.hpp>
#include <sge/config/config_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

std::filesystem::path sanguis::client::config::homedir()
{
  return sge::config::config_path(sanguis::config_app_name());
}
