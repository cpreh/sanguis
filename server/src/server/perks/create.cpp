#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/perks/choleric.hpp>
#include <sanguis/server/perks/create.hpp>
#include <sanguis/server/perks/fire_damage.hpp>
#include <sanguis/server/perks/health.hpp>
#include <sanguis/server/perks/ias.hpp>
#include <sanguis/server/perks/ims.hpp>
#include <sanguis/server/perks/irs.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sanguis/server/perks/piercing_damage.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::server::perks::unique_ptr sanguis::server::perks::create(
    sanguis::diff_clock_cref const _diff_clock,
    sanguis::random_generator_ref const _random_generator,
    sanguis::perk_type const _type)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_type)
  {
  case sanguis::perk_type::choleric:
    return fcppt::unique_ptr_to_base<sanguis::server::perks::perk>(
        fcppt::make_unique_ptr<sanguis::server::perks::choleric>(_diff_clock, _random_generator));
  case sanguis::perk_type::health:
    return fcppt::unique_ptr_to_base<sanguis::server::perks::perk>(
        fcppt::make_unique_ptr<sanguis::server::perks::health>());
  case sanguis::perk_type::fire_damage:
    return fcppt::unique_ptr_to_base<sanguis::server::perks::perk>(
        fcppt::make_unique_ptr<sanguis::server::perks::fire_damage>());
  case sanguis::perk_type::piercing_damage:
    return fcppt::unique_ptr_to_base<sanguis::server::perks::perk>(
        fcppt::make_unique_ptr<sanguis::server::perks::piercing_damage>());
  case sanguis::perk_type::ias:
    return fcppt::unique_ptr_to_base<sanguis::server::perks::perk>(
        fcppt::make_unique_ptr<sanguis::server::perks::ias>());
  case sanguis::perk_type::ims:
    return fcppt::unique_ptr_to_base<sanguis::server::perks::perk>(
        fcppt::make_unique_ptr<sanguis::server::perks::ims>());
  case sanguis::perk_type::irs:
    return fcppt::unique_ptr_to_base<sanguis::server::perks::perk>(
        fcppt::make_unique_ptr<sanguis::server::perks::irs>());
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_type);
}
