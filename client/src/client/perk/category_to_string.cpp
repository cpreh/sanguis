#include <sanguis/client/perk/category.hpp>
#include <sanguis/client/perk/category_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string
sanguis::client::perk::category_to_string(sanguis::client::perk::category const _category)
{
#define SANGUIS_CATEGORY_CASE(name) \
  case sanguis::client::perk::category::name: \
    return FCPPT_TEXT(#name)

  switch (_category)
  {
    SANGUIS_CATEGORY_CASE(attack);
    SANGUIS_CATEGORY_CASE(survival);
  }

#undef SANGUIS_CATEGORY_CASE

  FCPPT_ASSERT_UNREACHABLE;
}
