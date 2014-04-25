#include <sanguis/client/load/animation_name.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/lookup_animation_name.hpp>
#include <sanguis/model/animation_name.hpp>
#include <fcppt/enum_size.hpp>
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
	sanguis::model::animation_name,
	fcppt::enum_size<
		sanguis::client::load::animation_type
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
				sanguis::client::load::animation_name(
					fcppt::cast::int_to_enum<
						sanguis::client::load::animation_type
					>(
						_index
					)
				);
		}
	)
);

}

sanguis::client::load::animation_type
sanguis::client::load::model::lookup_animation_name(
	sanguis::model::animation_name const &_name
)
{
	return
		fcppt::cast::int_to_enum<
			sanguis::client::load::animation_type
		>(
			std::distance(
				animation_types.begin(),
				fcppt::algorithm::find_exn(
					animation_types.begin(),
					animation_types.end(),
					_name
				)
			)
		);

}
