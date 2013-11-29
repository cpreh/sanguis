#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/update_result_fwd.hpp>
#include <sanguis/server/ai/visible_fwd.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/property/change_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class simple
:
	public sanguis::server::ai::base
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	simple(
		sanguis::server::entities::with_ai &,
		sanguis::server::ai::sight_range
	);

	~simple();
private:
	sanguis::server::entities::auto_weak_link
	target() const
	override;

	sanguis::server::ai::sight_range const
	sight_range() const
	override;

	sanguis::server::ai::update_result
	in_range(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::server::ai::update_result
	out_of_range(
		sanguis::server::entities::with_body &
	)
	override;

	sanguis::server::ai::update_result
	distance_changes(
		sanguis::server::entities::with_body &,
		sanguis::server::ai::visible
	)
	override;

	sanguis::server::ai::update_result
	on_health_change(
		sanguis::server::ai::entity_set const &,
		sanguis::server::entities::property::change_event const &
	)
	override;

	sanguis::server::ai::update_result
	update_target(
		sanguis::server::entities::with_body &
	);

	sanguis::server::ai::update_result
	lose_target(
		sanguis::server::entities::with_body &
	);

	sanguis::server::entities::with_ai &me_;

	sanguis::server::ai::sight_range const sight_range_;

	sanguis::server::entities::auto_weak_link target_;
};

}
}
}

#endif
