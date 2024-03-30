#include <sanguis/client/perk/category.hpp>
#include <sanguis/client/perk/category_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

fcppt::string
sanguis::client::perk::category_to_string(sanguis::client::perk::category const _category)
{
#define SANGUIS_CATEGORY_CASE(name) \
  case sanguis::client::perk::category::name: \
    return FCPPT_TEXT(#name)

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_category)
  {
    SANGUIS_CATEGORY_CASE(attack);
    SANGUIS_CATEGORY_CASE(survival);
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_category);

#undef SANGUIS_CATEGORY_CASE
}
