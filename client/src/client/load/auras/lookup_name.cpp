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
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

typedef
fcppt::enum_::array<
	sanguis::aura_type,
	fcppt::string
>
aura_type_array;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

aura_type_array const aura_types(
	fcppt::enum_::array_init<
		aura_type_array
	>(
		&sanguis::client::load::aura_name
	)
);

FCPPT_PP_POP_WARNING

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
