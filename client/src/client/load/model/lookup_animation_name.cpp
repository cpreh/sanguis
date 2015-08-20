#include <sanguis/exception.hpp>
#include <sanguis/client/load/animation_name.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/lookup_animation_name.hpp>
#include <sanguis/model/animation_name.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/algorithm/index_of_enum_array.hpp>
#include <fcppt/container/enum_array.hpp>


namespace
{

typedef
fcppt::container::enum_array<
	sanguis::client::load::animation_type,
	sanguis::model::animation_name
>
animation_type_array;

animation_type_array const animation_types(
	fcppt::algorithm::enum_array_fold<
		animation_type_array
	>(
		&sanguis::client::load::animation_name
	)
);

}

sanguis::client::load::animation_type
sanguis::client::load::model::lookup_animation_name(
	sanguis::model::animation_name const &_name
)
{
	return
		fcppt::optional_to_exception(
			fcppt::algorithm::index_of_enum_array(
				animation_types,
				_name
			),
			[
				&_name
			]{
				return
					sanguis::exception{
						FCPPT_TEXT("lookup_animation_name ")
						+
						_name.get()
						+
						FCPPT_TEXT(" failed!")
					};
			}
		);
}
