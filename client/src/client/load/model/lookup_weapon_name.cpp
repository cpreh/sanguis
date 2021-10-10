#include <sanguis/exception.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/primary_weapon_type.hpp>
#include <sanguis/client/load/primary_weapon_name.hpp>
#include <sanguis/client/load/model/lookup_weapon_name.hpp>
#include <sanguis/model/weapon_category_name.hpp>
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

using weapon_type_array =
    fcppt::enum_::array<sanguis::primary_weapon_type, sanguis::model::weapon_category_name>;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)
FCPPT_PP_DISABLE_CLANG_WARNING(-Wexit-time-destructors)

// NOLINTNEXTLINE(cert-err58-cpp)
weapon_type_array const weapon_types(
    fcppt::enum_::array_init<weapon_type_array>(&sanguis::client::load::primary_weapon_name));

FCPPT_PP_POP_WARNING

}

sanguis::optional_primary_weapon_type
sanguis::client::load::model::lookup_weapon_name(sanguis::model::weapon_category_name const &_name)
{
  return _name.get() == FCPPT_TEXT("none")
             ? sanguis::optional_primary_weapon_type()
             : sanguis::optional_primary_weapon_type(fcppt::optional::to_exception(
                   fcppt::enum_::index_of_array(weapon_types, _name),
                   [&_name]
                   {
                     return sanguis::exception{
                         FCPPT_TEXT("lookup_weapon_name ") + _name.get() + FCPPT_TEXT(" failed!")};
                   }));
}
