#include <sanguis/client/config/homedir.hpp>
#include <sanguis/client/config/settings/file.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

std::filesystem::path sanguis::client::config::settings::file()
{
  return sanguis::client::config::homedir() / FCPPT_TEXT("settings.ini");
}
