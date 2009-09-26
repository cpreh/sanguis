#include "castpoint.hpp"
#include "backswing.hpp"
#include "ready.hpp"
#include "../delayed_attack.hpp"
#include "../events/shoot.hpp"
#include "../events/poll.hpp"
#include "../events/stop.hpp"
#include "../../entities/with_weapon.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/optional_impl.hpp>

sanguis::server::weapons::states::castpoint::castpoint(
	my_context ctx
)
:
	my_base(ctx),
	diff_clock_(),
	attack_time(
		context<
			weapon
		>().cast_point(),
		sge::time::activation_state::active,
		diff_clock_.callback()
	),
	attack_dest()
{}


boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	events::shoot const &e
)
{
	attack_dest = e.to();
	return discard_event();
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	events::poll const &e
)
{
	diff_clock_.update(
		e.time() * context<weapon>().ias()
	);

	if(!attack_time.expired())
		return discard_event();
	
	context<
		weapon
	>().do_attack(
		delayed_attack(
			e.owner().center(),
			e.owner().angle(),
			e.owner().team(),
			e.owner().environment(),
			*attack_dest
		)
	);

	context<weapon>().on_castpoint(
		e.owner()
	);

	post_event(e);

	return transit<backswing>();
}

boost::statechart::result
sanguis::server::weapons::states::castpoint::react(
	events::stop const &
)
{
	return transit<ready>();
}
