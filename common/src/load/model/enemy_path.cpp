#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/load/enemy_name.hpp>
#include <sanguis/load/model/enemy_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::path
sanguis::load::model::enemy_path(
	sanguis::creator::enemy_type const _type
)
{
	return
		sanguis::load::model::path{
			std::filesystem::path{
				FCPPT_TEXT("enemies")
			}
			/
			sanguis::load::enemy_name(
				_type
			)
		};
}
