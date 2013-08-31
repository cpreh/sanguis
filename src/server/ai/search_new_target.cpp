#include <sanguis/server/closest_entity.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/search_new_target.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/optional_impl.hpp>


sanguis::server::entities::auto_weak_link const
sanguis::server::ai::search_new_target(
	sanguis::server::entities::base const &_me,
	sanguis::server::ai::entity_set const &_entities
)
{
	typedef
	fcppt::optional<
		sanguis::server::entities::with_body &
	>
	result_type;

	result_type const result(
		sanguis::server::closest_entity(
			_me,
			_entities,
			[](
				sanguis::server::entities::with_body const &
			)
			{
				// All potential targets for now
				return true;
			}
		)
	);

	return
		result
		?
			result->link()
		:
			sanguis::server::entities::auto_weak_link()
		;
}
