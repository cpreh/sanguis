#include "homedir.hpp"
#include <sge/config/config_path.hpp>
#include <fcppt/text.hpp>

fcppt::filesystem::path const
sanguis::client::config::homedir()
{
	return
		sge::config::config_path(
			FCPPT_TEXT("sanguis")
		);
}
