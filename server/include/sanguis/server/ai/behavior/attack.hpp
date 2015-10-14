#ifndef SANGUIS_SERVER_AI_BEHAVIOR_ATTACK_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_ATTACK_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor_fwd.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/optional_with_body_ref_fwd.hpp>
#include <sanguis/server/entities/transfer_result_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/property/change_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

class attack
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONCOPYABLE(
		attack
	);
public:
	attack(
		sanguis::server::ai::context &,
		sanguis::server::ai::sight_range
	);

	~attack()
	override;

	sanguis::server::entities::transfer_result
	transfer()
	override;

	bool
	start()
	override;

	sanguis::server::ai::status
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

	void
	health_changed(
		sanguis::server::entities::property::change_event const &
	);

	sanguis::server::entities::optional_with_body_ref
	closest_visible_target() const;

	virtual
	sanguis::server::ai::speed_factor
	speed_factor() const;

	sanguis::server::ai::sight_range const sight_range_;

	sanguis::server::ai::entity_set potential_targets_;

	sanguis::server::entities::auto_weak_link target_;

	fcppt::signal::auto_connection const health_connection_;
};

}
}
}
}

#endif
