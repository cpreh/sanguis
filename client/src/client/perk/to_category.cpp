#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/category.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <fcppt/assert/unreachable.hpp>

sanguis::client::perk::category sanguis::client::perk::to_category(sanguis::perk_type const _type)
{
  switch (_type)
  {
  case sanguis::perk_type::choleric:
    return sanguis::client::perk::category::attack;
  case sanguis::perk_type::health:
    return sanguis::client::perk::category::survival;
  case sanguis::perk_type::fire_damage:
    return sanguis::client::perk::category::attack;
  case sanguis::perk_type::piercing_damage:
    return sanguis::client::perk::category::attack;
  case sanguis::perk_type::ias:
    return sanguis::client::perk::category::attack;
  case sanguis::perk_type::ims:
    return sanguis::client::perk::category::survival;
  case sanguis::perk_type::irs:
    return sanguis::client::perk::category::attack;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
