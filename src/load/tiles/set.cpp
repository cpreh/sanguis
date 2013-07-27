#include <sanguis/media_path.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/tiles/category.hpp>
#include <sanguis/load/tiles/name.hpp>
#include <sanguis/load/tiles/orientation.hpp>
#include <sanguis/load/tiles/set.hpp>
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
	sanguis::load::tiles::category const &_category,
	sanguis::load::tiles::name const &_name
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
			_category.get()
			/
			_name.get()
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
			_category
			<<
			FCPPT_TEXT('/')
			<<
			_name
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
