#include <sanguis/tiles/direction.hpp>
#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/impl/orientation_to_string.hpp>
#include <fcppt/make_enum_range.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>


fcppt::string
sanguis::tiles::impl::orientation_to_string(
	sanguis::tiles::orientation const _orientation
)
{
	return
		fcppt::algorithm::map<
			fcppt::string
		>(
			fcppt::make_enum_range<
				sanguis::tiles::direction
			>(),
			[
				_orientation
			](
				sanguis::tiles::direction const _dir
			)
			{
				return
					_orientation[
						_dir
					]
					?
						FCPPT_TEXT('1')
					:
						FCPPT_TEXT('0')
					;
			}
		);
}
