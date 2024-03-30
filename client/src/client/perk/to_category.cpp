#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/category.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::client::perk::category sanguis::client::perk::to_category(sanguis::perk_type const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sanguis::perk_type::choleric:
  case sanguis::perk_type::fire_damage:
  case sanguis::perk_type::piercing_damage:
  case sanguis::perk_type::ias:
  case sanguis::perk_type::irs:
    return sanguis::client::perk::category::attack;
  case sanguis::perk_type::ims:
  case sanguis::perk_type::health:
    return sanguis::client::perk::category::survival;
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
