#include <sanguis/tiles/orientation.hpp>
#include <sanguis/tiles/impl/orientation_to_string.hpp>
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
			_orientation,
			[](
				bool const _value
			)
			{
				return
					_value
					?
						FCPPT_TEXT('1')
					:
						FCPPT_TEXT('0')
					;
			}
		);
}
