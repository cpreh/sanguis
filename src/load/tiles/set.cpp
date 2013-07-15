#include <sanguis/media_path.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/tiles/orientation.hpp>
#include <sanguis/load/tiles/set.hpp>
#include <sanguis/load/tiles/to_name.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/bitfield/underlying_value.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::tiles::set::set(
	sanguis::load::resource::textures const &_textures,
	sanguis::creator::tile const _tile
)
:
	elements_()
{
	for(
		boost::filesystem::directory_iterator it(
			sanguis::media_path()
			/
			FCPPT_TEXT("tiles")
			/
			sanguis::load::tiles::to_name(
				_tile
			)
		);
		it != boost::filesystem::directory_iterator();
		++it
	)
	{
		boost::filesystem::path const path(
			it->path()
		);

		fcppt::optional<
			sanguis::load::tiles::set::orientation_internal_type
		> const number(
			fcppt::extract_from_string<
				sanguis::load::tiles::set::orientation_internal_type
			>(
				fcppt::filesystem::stem(
					path
				)
			)
		);

		if(
			!number
		)
		{
			FCPPT_LOG_ERROR(
				sanguis::load::log(),
				fcppt::log::_
				<<
				FCPPT_TEXT("Tileset file ")
				<<
				fcppt::filesystem::path_to_string(
					path
				)
				<<
				FCPPT_TEXT(" has an invalid filename.")
			);

			continue;
		}

		elements_.insert(
			std::make_pair(
				*number,
				_textures.load(
					path
				)
			)
		);
	}

	if(
		!this->orientation(
			sanguis::load::tiles::orientation::null()
		)
	)
		FCPPT_LOG_ERROR(
			sanguis::load::log(),
			fcppt::log::_
			<<
			FCPPT_TEXT("Tileset ")
			<<
			sanguis::load::tiles::to_name(
				_tile
			)
			<<
			FCPPT_TEXT(" has no default orientation.")
		);
}

sanguis::load::tiles::set::~set()
{
}

sge::texture::const_part_shared_ptr const
sanguis::load::tiles::set::orientation(
	sanguis::load::tiles::orientation const &_orientation
) const
{
	element_map::const_iterator const it(
		elements_.find(
			fcppt::container::bitfield::underlying_value(
				_orientation
			)
		)
	);

	return
		it == elements_.end()
		?
			sge::texture::const_part_shared_ptr()
		:
			it->second
		;
}
