#ifndef SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_FRIEND_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

class follow_friend
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONCOPYABLE(
		follow_friend
	);
public:
	follow_friend(
		sanguis::server::ai::context &,
		sanguis::server::ai::sight_range
	);

	~follow_friend()
	override;

	bool
	do_start()
	override;

	void
	do_stop()
	override;

	sanguis::server::ai::behavior::status
	update(
		sanguis::duration
	)
	override;
private:
	void
	target_enters(
		sanguis::server::entities::with_body &
	);

	void
	target_leaves(
		sanguis::server::entities::with_body &
	);

	sanguis::server::entities::auto_weak_link
	first_target() const;

	sanguis::server::ai::entity_set potential_targets_;

	sanguis::server::entities::auto_weak_link target_;
};

}
}
}
}

#endif
