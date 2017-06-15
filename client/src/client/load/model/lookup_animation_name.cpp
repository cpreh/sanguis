#include <sanguis/exception.hpp>
#include <sanguis/client/load/animation_name.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/lookup_animation_name.hpp>
#include <sanguis/model/animation_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/array.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/enum/index_of_array.hpp>
#include <fcppt/optional/to_exception.hpp>


namespace
{

typedef
fcppt::enum_::array<
	sanguis::client::load::animation_type,
	sanguis::model::animation_name
>
animation_type_array;

animation_type_array const animation_types(
	fcppt::enum_::array_init<
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
		fcppt::optional::to_exception(
			fcppt::enum_::index_of_array(
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
