#ifndef SANGUIS_SERVER_AI_BEHAVIOR_STAY_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_STAY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::ai::behavior
{

class stay
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONMOVABLE(
		stay
	);
public:
	explicit
	stay(
		sanguis::server::ai::context_ref
	);

	~stay()
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
	sanguis::server::center const start_pos_;
};

}

#endif
