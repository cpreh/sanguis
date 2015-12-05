#include <sanguis/aura_type.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/client/load/aura_name.hpp>
#include <sanguis/client/load/auras/lookup_name.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_init.hpp>
#include <fcppt/algorithm/index_of_enum_array.hpp>
#include <fcppt/container/enum_array.hpp>


namespace
{

typedef
fcppt::container::enum_array<
	sanguis::aura_type,
	fcppt::string
>
aura_type_array;

aura_type_array const aura_types(
	fcppt::algorithm::enum_array_init<
		aura_type_array
	>(
		&sanguis::client::load::aura_name
	)
);

}

sanguis::aura_type
sanguis::client::load::auras::lookup_name(
	fcppt::string const &_name
)
{
	return
		fcppt::optional_to_exception(
			fcppt::algorithm::index_of_enum_array(
				aura_types,
				_name
			),
			[
				&_name
			]{
				return
					sanguis::exception{
						FCPPT_TEXT("auras::lookup_name ")
						+
						_name
						+
						FCPPT_TEXT(" failed!")
					};
			}
		);
}
