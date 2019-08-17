#include <sanguis/weapon_type.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <sanguis/load/model/path.hpp>
#include <sanguis/load/model/weapon_pickup_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sanguis::load::model::path
sanguis::load::model::weapon_pickup_path(
	sanguis::weapon_type const _type
)
{
	return
		sanguis::load::model::path{
			std::filesystem::path{
				FCPPT_TEXT("weapon_pickups")
			}
			/
			sanguis::load::weapon_pickup_name(
				_type
			)
		};
}
