#include <sanguis/exception.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/client/load/primary_weapon_name.hpp>
#include <sanguis/client/load/model/lookup_weapon_name.hpp>
#include <sanguis/model/weapon_category_name.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>
#include <fcppt/algorithm/index_of_enum_array.hpp>
#include <fcppt/container/enum_array.hpp>


namespace
{

typedef
fcppt::container::enum_array<
	sanguis::primary_weapon_type,
	sanguis::model::weapon_category_name
>
weapon_type_array;

weapon_type_array const weapon_types(
	fcppt::algorithm::enum_array_init<
		weapon_type_array
	>(
		&sanguis::client::load::primary_weapon_name
	)
);

}

sanguis::optional_primary_weapon_type
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
				fcppt::optional_to_exception(
					fcppt::algorithm::index_of_enum_array(
						weapon_types,
						_name
					),
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
		;
}
