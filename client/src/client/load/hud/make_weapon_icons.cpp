#include <sanguis/media_path.hpp>
#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/log.hpp>
#include <sanguis/client/load/hud/make_weapon_icons.hpp>
#include <sanguis/client/load/hud/weapon_icon_map.hpp>
#include <sanguis/client/load/hud/weapon_type.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>




sanguis::client::load::hud::weapon_icon_map
sanguis::client::load::hud::make_weapon_icons(
	sanguis::client::load::resource::textures const &_textures
)
{
	sanguis::client::load::hud::weapon_icon_map result;

	// TODO: map_optional?
	for(
		boost::filesystem::path const &path
		:
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
		)
	)
	{
		sanguis::optional_weapon_type const weapon_type(
			sanguis::client::load::hud::weapon_type(
				fcppt::filesystem::stem(
					path
				)
			)
		);

		if(
			!weapon_type
		)
		{
			FCPPT_LOG_WARNING(
				sanguis::client::load::log(),
				fcppt::log::_
					<<
					FCPPT_TEXT("Hud weapon icon ")
					<<
					fcppt::filesystem::path_to_string(
						path
					)
					<<
					FCPPT_TEXT(" is not recognized.")
			);

			continue;
		}

		FCPPT_ASSERT_ERROR(
			result.insert(
				std::make_pair(
					*weapon_type,
					fcppt::make_cref(
						_textures.load(
							path
						)
					)
				)
			).second
		);
	}

	return
		result;
}
