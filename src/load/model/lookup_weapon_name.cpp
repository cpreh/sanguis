#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/load/primary_weapon_name.hpp>
#include <sanguis/load/model/lookup_weapon_name.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/array_fold.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::array<
	fcppt::string,
	static_cast<
		std::size_t
	>(
		fcppt::enum_size<
			sanguis::primary_weapon_type
		>::value
	)
> weapon_type_array;

weapon_type_array const weapon_types(
	fcppt::algorithm::array_fold<
		weapon_type_array
	>(
		[](
			std::size_t const _index
		)
		{
			return
				sanguis::load::primary_weapon_name(
					static_cast<
						sanguis::primary_weapon_type
					>(
						_index
					)
				);
		}
	)
);

}

sanguis::optional_primary_weapon_type const
sanguis::load::model::lookup_weapon_name(
	fcppt::string const &_str
)
{
	return
		_str
		==
		FCPPT_TEXT("none")
		?
			sanguis::optional_primary_weapon_type()
		:
			sanguis::optional_primary_weapon_type(
				static_cast<
					sanguis::primary_weapon_type
				>(
					std::distance(
						weapon_types.begin(),
						fcppt::algorithm::find_exn(
							weapon_types.begin(),
							weapon_types.end(),
							_str
						)
					)
				)
			)
		;
}
