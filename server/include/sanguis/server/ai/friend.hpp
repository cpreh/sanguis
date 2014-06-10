#ifndef SANGUIS_SERVER_AI_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_AI_FRIEND_HPP_INCLUDED

#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/update_result_fwd.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class friend_
:
	public sanguis::server::ai::simple
{
	FCPPT_NONCOPYABLE(
		friend_
	);
public:
	friend_(
		sanguis::server::entities::with_ai &,
		sanguis::server::ai::sight_range,
		sanguis::server::entities::spawn_owner const &
	);

	~friend_()
	override;
private:
	sanguis::server::ai::update_result
	lose_target(
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
	does_patrolling() const
	override;

	sanguis::server::entities::spawn_owner const spawn_owner_;
};

}
}
}

#endif
