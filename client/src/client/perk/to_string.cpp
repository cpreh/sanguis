#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sanguis::client::perk::to_string(sanguis::perk_type const _type)
{
  switch (_type)
  {
  case sanguis::perk_type::choleric:
    return FCPPT_TEXT("choleric");
  case sanguis::perk_type::health:
    return FCPPT_TEXT("health");
  case sanguis::perk_type::fire_damage:
    return FCPPT_TEXT("fire damage");
  case sanguis::perk_type::piercing_damage:
    return FCPPT_TEXT("piercing damage");
  case sanguis::perk_type::ias:
    return FCPPT_TEXT("increased attack speed");
  case sanguis::perk_type::ims:
    return FCPPT_TEXT("increased movement speed");
  case sanguis::perk_type::irs:
    return FCPPT_TEXT("increased reload speed");
  }

  FCPPT_ASSERT_UNREACHABLE;
}
