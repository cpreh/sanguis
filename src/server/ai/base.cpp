#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/update_result.hpp>
#include <sanguis/server/ai/visible.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/property/change_event_fwd.hpp>


sanguis::server::ai::base::base()
{
}

sanguis::server::ai::base::~base()
{
}

sanguis::server::ai::update_result
sanguis::server::ai::base::in_range(
	sanguis::server::entities::with_body &
)
{
	return
		sanguis::server::ai::update_result::keep_target;
}

sanguis::server::ai::update_result
sanguis::server::ai::base::distance_changes(
	sanguis::server::entities::with_body &,
	sanguis::server::ai::visible
)
{
	return
		sanguis::server::ai::update_result::keep_target;
}

sanguis::server::ai::update_result
sanguis::server::ai::base::out_of_range(
	sanguis::server::entities::with_body &
)
{
	return
		sanguis::server::ai::update_result::keep_target;
}

sanguis::server::ai::update_result
sanguis::server::ai::base::on_health_change(
	sanguis::server::ai::entity_set const &,
	sanguis::server::entities::property::change_event const &
)
{
	return
		sanguis::server::ai::update_result::keep_target;
}

bool
sanguis::server::ai::base::aggressive() const
{
	return
		true;
}

bool
sanguis::server::ai::base::target_friends() const
{
	return
		false;
}
