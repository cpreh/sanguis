#ifndef SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED

#include "../control/action_type.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class action
:
	public boost::statechart::event<
		action
	>
{
	FCPPT_NONASSIGNABLE(
		action
	)
public:
	explicit action(
		control::action_type
	);

	control::action_type::type
	type() const;
private:
	control::action_type const type_;
};

}
}
}

#endif
