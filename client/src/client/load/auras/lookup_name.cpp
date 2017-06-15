#include <sanguis/aura_type.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/client/load/aura_name.hpp>
#include <sanguis/client/load/auras/lookup_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/array.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/enum/index_of_array.hpp>
#include <fcppt/optional/to_exception.hpp>


namespace
{

typedef
fcppt::enum_::array<
	sanguis::aura_type,
	fcppt::string
>
aura_type_array;

aura_type_array const aura_types(
	fcppt::enum_::array_init<
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
		fcppt::optional::to_exception(
			fcppt::enum_::index_of_array(
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
