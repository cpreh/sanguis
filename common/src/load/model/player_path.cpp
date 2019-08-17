#include <sanguis/load/model/path.hpp>
#include <sanguis/load/model/player_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::path
sanguis::load::model::player_path()
{
	return
		sanguis::load::model::path{
			std::filesystem::path{
				FCPPT_TEXT("player")
			}
		};
}
