#include <sanguis/exception.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/client/load/primary_weapon_name.hpp>
#include <sanguis/client/load/model/lookup_weapon_name.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/array_fold.hpp>
#include <fcppt/algorithm/find_exn.hpp>
#include <fcppt/cast/int_to_enum.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef std::array<
	sanguis::model::weapon_category_name,
	fcppt::cast::size<
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
				sanguis::client::load::primary_weapon_name(
					fcppt::cast::int_to_enum<
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
sanguis::client::load::model::lookup_weapon_name(
	sanguis::model::weapon_category_name const &_name
)
{
	return
		_name.get()
		==
		FCPPT_TEXT("none")
		?
			sanguis::optional_primary_weapon_type()
		:
			sanguis::optional_primary_weapon_type(
				fcppt::cast::int_to_enum<
					sanguis::primary_weapon_type
				>(
					std::distance(
						weapon_types.begin(),
						fcppt::algorithm::find_exn(
							weapon_types.begin(),
							weapon_types.end(),
							_name,
							[
								&_name
							]{
								return
									sanguis::exception{
										FCPPT_TEXT("lookup_weapon_name ")
										+
										_name.get()
										+
										FCPPT_TEXT(" failed!")
									};
							}
						)
					)
				)
			)
		;
}
