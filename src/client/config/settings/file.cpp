#include <sanguis/client/config/settings/file.hpp>
#include <sanguis/client/config/homedir.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

boost::filesystem::path const
sanguis::client::config::settings::file()
{
	return
		config::homedir()
		/ FCPPT_TEXT("settings.ini");
}
