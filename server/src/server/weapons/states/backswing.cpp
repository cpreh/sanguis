#include <sanguis/diff_timer.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/weapons/log.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll.hpp>
#include <sanguis/server/weapons/events/reload.hpp>
#include <sanguis/server/weapons/events/shoot.hpp>
#include <sanguis/server/weapons/events/stop.hpp>
#include <sanguis/server/weapons/states/backswing.hpp>
#include <sanguis/server/weapons/states/castpoint.hpp>
#include <sanguis/server/weapons/states/idle.hpp>
#include <sanguis/server/weapons/states/reloading.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::weapons::states::backswing::backswing(my_context _ctx)
    : my_base(_ctx),
      cancelled_(false),
      cooldown_(sanguis::diff_timer::parameters(
          fcppt::make_cref(this->context<sanguis::server::weapons::weapon>().diff_clock()),
          this->context<sanguis::server::weapons::weapon>().backswing_time().get() /
              this->context<sanguis::server::weapons::weapon>().owner().ias().get())){
          FCPPT_LOG_VERBOSE(
              this->context<sanguis::server::weapons::weapon>().log().main_log(),
              fcppt::log::out << FCPPT_TEXT("backswing: ") << this)}

      FCPPT_PP_POP_WARNING

      sanguis::server::weapons::states::backswing::~backswing() = default;

boost::statechart::result
sanguis::server::weapons::states::backswing::react(sanguis::server::weapons::events::poll const &)
{
  if (!cooldown_.expired())
  {
    return this->discard_event();
  }

  if (this->context<sanguis::server::weapons::weapon>().magazine_empty())
  {
    return this->react(sanguis::server::weapons::events::reload());
  }

  return cancelled_ ? this->transit<sanguis::server::weapons::states::idle>()
                    : this->transit<sanguis::server::weapons::states::castpoint>();
}

boost::statechart::result
sanguis::server::weapons::states::backswing::react(sanguis::server::weapons::events::reload const &)
{
  if (!this->context<sanguis::server::weapons::weapon>().reload_time().has_value())
  {
    return this->discard_event();
  }

  if (!cancelled_)
  {
    this->post_event(sanguis::server::weapons::events::shoot());
  }

  return this->transit<sanguis::server::weapons::states::reloading>();
}

boost::statechart::result
sanguis::server::weapons::states::backswing::react(sanguis::server::weapons::events::stop const &)
{
  cancelled_ = true;

  return this->discard_event();
}
