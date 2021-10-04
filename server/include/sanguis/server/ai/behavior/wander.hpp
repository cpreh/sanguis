#ifndef SANGUIS_SERVER_AI_BEHAVIOR_WANDER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_WANDER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::ai::behavior
{

class wander
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONMOVABLE(
		wander
	);
public:
	wander(
		sanguis::server::ai::context_ref,
		sanguis::random_generator_ref,
		sanguis::server::ai::speed_factor
	);

	~wander()
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

	sanguis::server::ai::speed_factor const speed_factor_;
};

}

#endif
