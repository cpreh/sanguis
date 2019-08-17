#include <sanguis/projectile_type.hpp>
#include <sanguis/load/projectile_name.hpp>
#include <sanguis/load/model/path.hpp>
#include <sanguis/load/model/projectile_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::path
sanguis::load::model::projectile_path(
	sanguis::projectile_type const _type
)
{
	return
		sanguis::load::model::path{
			std::filesystem::path{
				FCPPT_TEXT("projectiles")
			}
			/
			sanguis::load::projectile_name(
				_type
			)
		};
}
