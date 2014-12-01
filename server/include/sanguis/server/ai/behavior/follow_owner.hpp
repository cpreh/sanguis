#ifndef SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_OWNER_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BEHAVIOR_FOLLOW_OWNER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status_fwd.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{
namespace behavior
{

class follow_owner
:
	public sanguis::server::ai::behavior::base
{
	FCPPT_NONCOPYABLE(
		follow_owner
	);
public:
	follow_owner(
		sanguis::server::ai::context &,
		sanguis::server::entities::spawn_owner const &
	);

	~follow_owner()
	override;

	bool
	start()
	override;

	sanguis::server::ai::behavior::status
	update(
		sanguis::duration
	)
	override;
private:
	sanguis::server::entities::spawn_owner const spawn_owner_;
};

}
}
}
}

#endif
