#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/closest_entity.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_target.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/auras/target.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/optional_with_body_ref.hpp>
#include <sanguis/server/entities/same_object.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
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
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
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
	sanguis::server::ai::behavior::base(
		_context
	),
	sight_range_(
		_sight_range
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
}

sanguis::server::ai::behavior::attack::~attack()
{
}

sanguis::server::entities::transfer_result
sanguis::server::ai::behavior::attack::transfer()
{
	return
		sanguis::server::entities::transfer_result(
			this->me().add_aura(
				fcppt::make_unique_ptr<
					sanguis::server::auras::target
				>(
					sanguis::server::radius(
						sight_range_.get()
					),
					this->me().team(),
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
			)
		);
}

bool
sanguis::server::ai::behavior::attack::start()
{
	return
		target_.get().has_value()
		||
		fcppt::maybe(
			this->closest_visible_target(),
			[]{
				return
					false;
			},
			[
				this
			](
				sanguis::server::entities::with_body &_target
			)
			{
				target_ =
					_target.link();

				return
					true;
			}
		);
}

sanguis::server::ai::status
sanguis::server::ai::behavior::attack::update(
	sanguis::duration
)
{
	fcppt::maybe_void(
		this->closest_visible_target(),
		[
			this
		](
			sanguis::server::entities::with_body &_closer_target
		)
		{
			target_ =
				_closer_target.link();
		}
	);

	return
		fcppt::maybe(
			target_.get(),
			[]{
				return
					sanguis::server::ai::status::failure;
			},
			[
				this
			](
				sanguis::server::entities::with_links const &_target
			)
			{
				sanguis::server::ai::is_visible const is_visible{
					sanguis::creator::tile_is_visible(
						this->context().grid(),
						sanguis::server::world::center_to_grid_pos(
							_target.center()
						),
						sanguis::server::world::center_to_grid_pos(
							this->me().center()
						)
					)
				};

				this->me().target(
					is_visible.get()
					?
						sanguis::server::weapons::optional_target(
							sanguis::server::weapons::target(
								_target.center().get()
							)
						)
					:
						sanguis::server::weapons::optional_target()
				);

				sanguis::is_primary_weapon const weapon_to_use{
					true
				};

				sanguis::server::ai::in_range const in_range{
					this->me().in_range(
						weapon_to_use
					)
				};

				this->me().use_weapon(
					is_visible.get()
					&&
					in_range.get()
					,
					weapon_to_use
				);

				sanguis::server::ai::go_to_target(
					this->context(),
					in_range,
					is_visible,
					sanguis::server::ai::target{
						_target.center()
					},
					this->speed_factor()
				);

				return
					sanguis::server::ai::status::running;
			}
		);
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

	fcppt::maybe_void(
		target_.get(),
		[
			&_with_body,
			this
		](
			sanguis::server::entities::base const &_target
		)
		{
			if(
				sanguis::server::entities::same_object(
					_target,
					_with_body
				)
			)
				target_ =
					sanguis::server::entities::auto_weak_link();
		}
	);
}

void
sanguis::server::ai::behavior::attack::health_changed(
	sanguis::server::entities::property::change_event const &_event
)
{
	if(
		target_.get().has_value()
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

	fcppt::maybe_void(
		sanguis::server::closest_entity(
			this->me(),
			potential_targets_,
			[](
				sanguis::server::entities::with_body const &
			)
			{
				return
					true;
			}
		),
		[
			this
		](
			sanguis::server::entities::with_body &_result
		)
		{
			target_ =
				_result.link();
		}
	);
}

sanguis::server::entities::optional_with_body_ref
sanguis::server::ai::behavior::attack::closest_visible_target() const
{
	return
		sanguis::server::closest_entity(
			this->me(),
			potential_targets_,
			[
				this
			](
				sanguis::server::entities::with_body const &_ref
			)
			{
				return
					sanguis::creator::tile_is_visible(
						this->context().grid(),
						sanguis::server::world::center_to_grid_pos(
							_ref.center()
						),
						sanguis::server::world::center_to_grid_pos(
							this->me().center()
						)
					);
			}
		);
}

sanguis::server::ai::speed_factor const
sanguis::server::ai::behavior::attack::speed_factor() const
{
	return
		fcppt::literal<
			sanguis::server::ai::speed_factor
		>(
			1
		);
}
