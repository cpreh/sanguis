#include "file.hpp"
#include "../homedir.hpp"
#include <fcppt/text.hpp>

fcppt::filesystem::path const
sanguis::client::config::settings::file()
{
	return
		config::homedir()
		/ FCPPT_TEXT("settings.ini");
}
