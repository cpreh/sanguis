#ifndef SANGUIS_SERVER_WEAPONS_STATES_READY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_READY_HPP_INCLUDED

#include "ready_fwd.hpp"
#include "../weapon.hpp"
#include "../events/shoot_fwd.hpp"
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class ready
: public
	boost::statechart::simple_state<
		ready,
		weapon
	>
{
public:
	typedef boost::statechart::custom_reaction<
		events::shoot
	> reactions;

	boost::statechart::result
	react(
		events::shoot const &);
};

}
}
}
}

#endif
