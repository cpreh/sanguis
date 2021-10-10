#ifndef SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_HPP_INCLUDED

#include <sanguis/diff_timer.hpp>
#include <sanguis/state_override.hpp>
#include <sanguis/server/weapons/irs.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/events/poll_fwd.hpp>
#include <sanguis/server/weapons/events/reload_fwd.hpp>
#include <sanguis/server/weapons/events/stop_fwd.hpp>
#include <sanguis/server/weapons/states/backswing_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/list/list10.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/state.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::weapons::states
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4265)

class backswing
    : public boost::statechart::
          state<sanguis::server::weapons::states::backswing, sanguis::server::weapons::weapon>
{
  FCPPT_NONMOVABLE(backswing);

public:
  using reactions = boost::mpl::list3<
      boost::statechart::custom_reaction<sanguis::server::weapons::events::poll>,
      boost::statechart::custom_reaction<sanguis::server::weapons::events::reload>,
      boost::statechart::custom_reaction<sanguis::server::weapons::events::stop>>;

  explicit backswing(my_context);

  ~backswing() SANGUIS_STATE_OVERRIDE;

  [[nodiscard]] boost::statechart::result react(sanguis::server::weapons::events::poll const &);

  [[nodiscard]] boost::statechart::result react(sanguis::server::weapons::events::reload const &);

  [[nodiscard]] boost::statechart::result react(sanguis::server::weapons::events::stop const &);

private:
  bool cancelled_;

  sanguis::diff_timer cooldown_;
};

FCPPT_PP_POP_WARNING

}

#endif
