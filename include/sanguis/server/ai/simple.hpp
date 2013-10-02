#ifndef SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_SIMPLE_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
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
	void
	in_range(
		sanguis::server::entities::with_body &
	)
	override;

	void
	distance_changes(
		sanguis::server::entities::with_body &
	)
	override;

	void
	update(
		sanguis::creator::grid const &
	)
	override;

	sanguis::server::ai::sight_range const
	sight_range() const
	override;

	sanguis::server::entities::with_ai &me_;

	sanguis::server::ai::sight_range const sight_range_;

	sanguis::server::entities::auto_weak_link target_;

	sanguis::server::ai::pathing::trail trail_;
};

}
}
}

#endif
