#ifndef SANGUIS_SERVER_AI_MANAGER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_MANAGER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/manager_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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

	sanguis::server::ai::base &ai_;

	sanguis::server::ai::entity_set potential_targets_;

	sanguis::diff_timer update_timer_;
};

}
}
}

#endif