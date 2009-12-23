#include "homedir.hpp"
#include <sge/config/find_config_path.hpp>
#include <sge/text.hpp>

fcppt::filesystem::path const
sanguis::client::config::homedir()
{
	return sge::config::find_config_path(
		SGE_TEXT("sanguis")
	);
}
