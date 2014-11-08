#ifndef SANGUIS_SERVER_AI_BEHAVIOR_STAY_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_STAY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/center.hpp>
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

class stay
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONCOPYABLE(
		stay
	);
public:
	explicit
	stay(
		sanguis::server::ai::context &
	);

	~stay()
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

	sanguis::server::center const start_pos_;
};

}
}
}
}

#endif
