#ifndef SANGUIS_SERVER_WEAPONS_STATES_EXHAUSTED_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_EXHAUSTED_HPP_INCLUDED

#include <sanguis/server/weapons/weapon.hpp>
#include <sanguis/server/weapons/states/exhausted_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/simple_state.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class exhausted
:
	public boost::statechart::simple_state<
		sanguis::server::weapons::states::exhausted,
		sanguis::server::weapons::weapon
	>
{
	FCPPT_NONCOPYABLE(
		exhausted
	);
public:
	exhausted();

	virtual
	~exhausted();
};

}
}
}
}

#endif

