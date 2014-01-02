#ifndef SANGUIS_SERVER_AI_MANAGER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_MANAGER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/ai/base_fwd.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/manager_fwd.hpp>
#include <sanguis/server/ai/update_result_fwd.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	manager(
		sanguis::diff_clock const &,
		sanguis::server::ai::base &,
		sanguis::server::entities::with_ai &
	);

	~manager();

	void
	update();
private:
	void
	target_enters(
		sanguis::server::entities::with_body &
	);

	void
	target_leaves(
		sanguis::server::entities::with_body &
	);

	void
	friend_enters(
		sanguis::server::entities::with_body &
	);

	void
	friend_leaves(
		sanguis::server::entities::with_body &
	);

	void
	update_target(
		sanguis::server::ai::update_result
	);

	sanguis::server::ai::base &ai_;

	sanguis::server::entities::with_ai &me_;

	sanguis::server::ai::entity_set potential_targets_;

	sanguis::diff_timer update_timer_;

	sanguis::server::ai::pathing::trail trail_;

	fcppt::signal::scoped_connection const health_change_callback_;
};

}
}
}

#endif
