#include <sanguis/optional_weapon_type.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/client/load/log.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sanguis/client/load/hud/weapon_type.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/variant/less.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::hud::context::context(
	sanguis::client::load::resource::textures const &_textures
)
:
	weapon_icons_()
{
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
			)
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
			weapon_icons_.insert(
				std::make_pair(
					*weapon_type,
					_textures.load(
						path
					)
				)
			).second
		);
	}
}

sanguis::client::load::hud::context::~context()
{
}

sge::texture::const_part_shared_ptr const
sanguis::client::load::hud::context::weapon_icon(
	sanguis::weapon_type const _weapon_type
)
{
	fcppt::optional<
		sge::texture::const_part_shared_ptr
	> const icon{
		fcppt::container::find_opt(
			weapon_icons_,
			_weapon_type
		)
	};

	FCPPT_ASSERT_ERROR(
		icon
	);

	return
		*icon;
}
