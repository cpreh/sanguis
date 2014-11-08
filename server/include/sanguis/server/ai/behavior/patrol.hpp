#ifndef SANGUIS_SERVER_AI_BEHAVIOR_PATROL_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_PATROL_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

class patrol
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONCOPYABLE(
		patrol
	);
public:
	patrol(
		sanguis::server::ai::context &,
		sanguis::random_generator &
	);

	~patrol()
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
	sanguis::server::ai::context &context_;

	sanguis::random_generator &random_generator_;

	sanguis::creator::pos const start_pos_;
};

}
}
}
}

#endif
