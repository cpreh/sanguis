#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/update_result.hpp>
#include <sanguis/server/ai/visible.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>


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
