#ifndef SANGUIS_SERVER_AI_BASE_HPP_INCLUDED
#define SANGUIS_SERVER_AI_BASE_HPP_INCLUDED

#include <sanguis/server/ai/base_fwd.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/optional_target_fwd.hpp>
#include <sanguis/server/ai/sight_range_fwd.hpp>
#include <sanguis/server/ai/update_result_fwd.hpp>
#include <sanguis/server/ai/visible_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/property/change_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace ai
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	virtual
	~base() = 0;

	virtual
	sanguis::server::ai::optional_target const
	target() const = 0;

	// This could dynamically change in the future!
	virtual
	sanguis::server::ai::sight_range const
	sight_range() const = 0;

	virtual
	sanguis::server::ai::update_result
	in_range(
		sanguis::server::entities::with_body &
	);

	virtual
	sanguis::server::ai::update_result
	distance_changes(
		sanguis::server::entities::with_body &,
		sanguis::server::ai::visible
	);

	virtual
	sanguis::server::ai::update_result
	out_of_range(
		sanguis::server::entities::with_body &
	);

	virtual
	sanguis::server::ai::update_result
	on_health_change(
		sanguis::server::ai::entity_set const &,
		sanguis::server::entities::property::change_event const &
	);

	virtual
	sanguis::server::ai::update_result
	friend_in_range(
		sanguis::server::entities::with_body &
	);

	virtual
	sanguis::server::ai::update_result
	friend_out_of_range(
		sanguis::server::entities::with_body &
	);

	virtual
	bool
	aggressive() const;

	virtual
	bool
	target_friends() const;
};

}
}
}

#endif
