#include <sanguis/load/animation_name.hpp>
#include <sanguis/load/animation_type.hpp>
#include <sanguis/load/model/lookup_animation_name.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/string.hpp>
#include <fcppt/algorithm/array_fold.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/cast/int_to_enum.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::array<
	fcppt::string,
	fcppt::enum_size<
		sanguis::load::animation_type
	>::value
> animation_type_array;

animation_type_array const animation_types(
	fcppt::algorithm::array_fold<
		animation_type_array
	>(
		[](
			std::size_t const _index
		)
		{
			return
				sanguis::load::animation_name(
					fcppt::cast::int_to_enum<
						sanguis::load::animation_type
					>(
						_index
					)
				);
		}
	)
);

}

sanguis::load::animation_type
sanguis::load::model::lookup_animation_name(
	fcppt::string const &_str
)
{
	return
		fcppt::cast::int_to_enum<
			sanguis::load::animation_type
		>(
			std::distance(
				animation_types.begin(),
				fcppt::algorithm::find_exn(
					animation_types.begin(),
					animation_types.end(),
					_str
				)
			)
		);

}
