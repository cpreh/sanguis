#ifndef SANGUIS_SERVER_WEAPONS_STATES_CASTPOINT_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_CASTPOINT_HPP_INCLUDED

#include "castpoint_fwd.hpp"
#include "../weapon.hpp"
#include "../events/poll_fwd.hpp"
#include "../events/shoot_fwd.hpp"
#include "../events/stop_fwd.hpp"
#include "../../vector.hpp"
#include "../../../diff_timer.hpp"
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class castpoint
:
	public boost::statechart::state<
		castpoint,
		weapon
	>
{
	FCPPT_NONCOPYABLE(
		castpoint
	);
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::shoot
		>,
		boost::statechart::custom_reaction<
			events::poll
		>,
		boost::statechart::custom_reaction<
			events::stop
		>
	> reactions;

	explicit castpoint(
		my_context
	);

	~castpoint();

	boost::statechart::result
	react(
		events::shoot const &
	);

	boost::statechart::result
	react(
		events::poll const &
	);

	boost::statechart::result
	react(
		events::stop const &
	);
private:
	sanguis::diff_timer attack_time_;

	fcppt::optional<
		server::vector
	> attack_dest_;
};

}
}
}
}

#endif
