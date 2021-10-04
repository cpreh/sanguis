#ifndef SANGUIS_SERVER_AI_BEHAVIOR_PATROL_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_PATROL_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::ai::behavior
{

class patrol
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONMOVABLE(
		patrol
	);
public:
	patrol(
		sanguis::server::ai::context_ref,
		sanguis::random_generator_ref
	);

	~patrol()
	override;

	[[nodiscard]]
	bool
	start()
	override;

	[[nodiscard]]
	sanguis::server::ai::status
	update(
		sanguis::duration
	)
	override;
private:
	sanguis::random_generator_ref const random_generator_;

	sanguis::creator::pos const start_pos_;
};

}

#endif
