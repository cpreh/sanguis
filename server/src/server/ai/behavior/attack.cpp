#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/closest_entity.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/go_to_target.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/auras/target.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/same_object.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/property/change_event.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <sanguis/server/weapons/optional_target.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::behavior::attack::attack(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::sight_range const _sight_range
)
:
	sanguis::server::ai::behavior::base(),
	context_(
		_context
	),
	potential_targets_(),
	target_(),
	health_connection_{
		_context.me().health().register_change_callback(
			std::bind(
				&sanguis::server::ai::behavior::attack::health_changed,
				this,
				std::placeholders::_1
			)
		)
	}
{
	_context.me().add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::target
		>(
			sanguis::server::radius(
				_sight_range.get()
			),
			context_.me().team(),
			sanguis::server::auras::target_kind::enemy,
			sanguis::server::add_target_callback(
				std::bind(
					&sanguis::server::ai::behavior::attack::target_enters,
					this,
					std::placeholders::_1
				)
			),
			sanguis::server::remove_target_callback(
				std::bind(
					&sanguis::server::ai::behavior::attack::target_leaves,
					this,
					std::placeholders::_1
				)
			)
		)
	);
}

sanguis::server::ai::behavior::attack::~attack()
{
}

bool
sanguis::server::ai::behavior::attack::do_start()
{
	if(
		target_
	)
		return
			true;

	target_ =
		this->closest_target();

	return
		target_
		&&
		sanguis::creator::tile_is_visible(
			context_.grid(),
			sanguis::server::world::center_to_grid_pos(
				target_->center()
			),
			sanguis::server::world::center_to_grid_pos(
				context_.me().center()
			)
		);
}

void
sanguis::server::ai::behavior::attack::do_stop()
{
	context_.clear_path();

	target_ =
		sanguis::server::entities::auto_weak_link();

	sanguis::server::ai::idle(
		context_.me()
	);
}

sanguis::server::ai::behavior::status
sanguis::server::ai::behavior::attack::update(
	sanguis::duration
)
{
	sanguis::server::entities::auto_weak_link const closer_target(
		this->closest_target()
	);

	if(
		closer_target
	)
		target_ =
			closer_target;

	if(
		!target_
	)
		return
			sanguis::server::ai::behavior::status::failure;

	sanguis::creator::pos const target_grid_pos{
		sanguis::server::world::center_to_grid_pos(
			target_->center()
		)
	};

	sanguis::server::ai::is_visible const is_visible{
		sanguis::creator::tile_is_visible(
			context_.grid(),
			target_grid_pos,
			sanguis::server::world::center_to_grid_pos(
				context_.me().center()
			)
		)
	};

	context_.me().target(
		is_visible.get()
		?
			sanguis::server::weapons::optional_target(
				sanguis::server::weapons::target(
					target_->center().get()
				)
			)
		:
			sanguis::server::weapons::optional_target()
	);

	sanguis::is_primary_weapon const weapon_to_use{
		true
	};

	sanguis::server::ai::in_range const in_range{
		context_.me().in_range(
			weapon_to_use
		)
	};

	context_.me().use_weapon(
		is_visible.get()
		&&
		in_range.get()
		,
		weapon_to_use
	);

	sanguis::server::ai::go_to_target(
		context_,
		in_range,
		is_visible,
		sanguis::server::ai::target{
			target_->center()
		},
		sanguis::server::ai::is_patrolling{
			false
		}
	);

	return
		sanguis::server::ai::behavior::status::running;
}

void
sanguis::server::ai::behavior::attack::target_enters(
	sanguis::server::entities::with_body &_with_body
)
{
	FCPPT_ASSERT_ERROR(
		potential_targets_.insert(
			fcppt::make_ref(
				_with_body
			)
		)
		.second
	);
}

void
sanguis::server::ai::behavior::attack::target_leaves(
	sanguis::server::entities::with_body &_with_body
)
{
	FCPPT_ASSERT_ERROR(
		potential_targets_.erase(
			fcppt::make_ref(
				_with_body
			)
		)
		==
		1u
	);

	if(
		target_
		&&
		sanguis::server::entities::same_object(
			*target_,
			_with_body
		)
	)
		target_ =
			sanguis::server::entities::auto_weak_link();
}

void
sanguis::server::ai::behavior::attack::health_changed(
	sanguis::server::entities::property::change_event const &_event
)
{
	if(
		target_
		||
		_event.diff().get()
		>=
		fcppt::literal<
			sanguis::server::entities::property::value
		>(
			0
		)
	)
		return;

	fcppt::optional<
		sanguis::server::entities::with_body &
	> const result(
		sanguis::server::closest_entity(
			context_.me(),
			potential_targets_,
			[](
				sanguis::server::entities::with_body const &
			)
			{
				return
					true;
			}
		)
	);

	if(
		result
	)
		target_ =
			result->link();
}

sanguis::server::entities::auto_weak_link
sanguis::server::ai::behavior::attack::closest_target() const
{
	sanguis::creator::pos const my_grid_pos(
		sanguis::server::world::center_to_grid_pos(
			context_.me().center()
		)
	);

	fcppt::optional<
		sanguis::server::entities::with_body &
	> const result(
		sanguis::server::closest_entity(
			context_.me(),
			potential_targets_,
			[
				this,
				my_grid_pos
			](
				sanguis::server::entities::with_body const &_ref
			)
			{
				return
					sanguis::creator::tile_is_visible(
						context_.grid(),
						sanguis::server::world::center_to_grid_pos(
							_ref.center()
						),
						my_grid_pos
					);
			}
		)
	);

	return
		result
		?
			result->link()
		:
			sanguis::server::entities::auto_weak_link();
}
