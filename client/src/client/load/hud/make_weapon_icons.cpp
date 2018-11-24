#include <sanguis/media_path.hpp>
#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/hud/make_weapon_icons.hpp>
#include <sanguis/client/load/hud/weapon_icon_map.hpp>
#include <sanguis/client/load/hud/weapon_type.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::hud::weapon_icon_map
sanguis::client::load::hud::make_weapon_icons(
	fcppt::log::object &_log,
	sanguis::client::load::resource::textures const &_textures
)
{
	return
		fcppt::algorithm::map_optional<
			sanguis::client::load::hud::weapon_icon_map
		>(
			boost::make_iterator_range(
				boost::filesystem::directory_iterator(
					sanguis::media_path()
					/
					FCPPT_TEXT("hud")
					/
					FCPPT_TEXT("icons")
					/
					FCPPT_TEXT("weapons")
				),
				boost::filesystem::directory_iterator()
			),
			[
				&_log,
				&_textures
			](
				boost::filesystem::path const &_path
			)
			{
				typedef
				fcppt::optional::object<
					sanguis::client::load::hud::weapon_icon_map::value_type
				>
				result_type;

				return
					fcppt::optional::maybe(
						sanguis::client::load::hud::weapon_type(
							fcppt::filesystem::stem(
								_path
							)
						),
						[
							&_log,
							&_path
						]
						{
							FCPPT_LOG_WARNING(
								_log,
								fcppt::log::out
									<<
									FCPPT_TEXT("Hud weapon icon ")
									<<
									fcppt::filesystem::path_to_string(
										_path
									)
									<<
									FCPPT_TEXT(" is not recognized.")
							)

							return
								result_type();
						},
						[
							&_textures,
							&_path
						](
							sanguis::weapon_type const _weapon_type
						)
						{
							return
								result_type(
									std::make_pair(
										_weapon_type,
										fcppt::make_cref(
											_textures.load(
												_path
											)
										)
									)
								);
						}
					);
			}
		);
}
