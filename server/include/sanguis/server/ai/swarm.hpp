#ifndef SANGUIS_SERVER_AI_SWARM_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SWARM_HPP_INCLUDED

#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/update_result_fwd.hpp>
#include <sanguis/server/entities/optional_with_ai_ref_fwd.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_ai_ref.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class swarm
:
	public sanguis::server::ai::simple
{
	FCPPT_NONCOPYABLE(
		swarm
	);
public:
	swarm(
		sanguis::server::entities::with_ai &,
		sanguis::server::ai::sight_range
	);

	~swarm()
	override;
private:
	sanguis::server::ai::update_result
	friend_in_range(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::server::ai::update_result
	friend_out_of_range(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::server::ai::update_result
	update_target(
		sanguis::server::entities::with_body &
	)
	override;

	bool
	aggressive() const
	override;

	bool
	target_friends() const
	override;

	sanguis::server::entities::optional_with_ai_ref const
	leader() const;

	sanguis::server::ai::update_result
	follow_leader();

	template<
		typename Function
	>
	void
	dispatch_swarm_ai(
		sanguis::server::entities::with_body &,
		Function const &
	);

	typedef
	std::set<
		sanguis::server::entities::with_ai_ref
	>
	with_ai_set;

	with_ai_set friends_;
};

}
}
}

#endif
