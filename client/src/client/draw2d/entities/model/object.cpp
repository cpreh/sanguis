#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/health_valid.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/speed_is_null.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time.hpp>
#include <sanguis/client/draw2d/entities/model/expand_orders.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/entities/model/part.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/model/part_fwd.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assert/unreachable_message.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/combine.hpp>
#include <boost/tuple/tuple.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::model::object::object(
	sanguis::client::draw2d::entities::model::parameters const &_parameters
)
:
	sanguis::client::draw2d::entities::model::object::object(
		_parameters,
		_parameters.load_parameters().collection()[
			_parameters.path()
		]
	)
{
}

sanguis::client::draw2d::entities::model::object::~object()
{
}

void
sanguis::client::draw2d::entities::model::object::update()
{
	sanguis::client::draw2d::entities::container::update();

	for(
		part_unique_ptr const &cur_part
		:
		parts_
	)
		cur_part->update();
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sanguis::client::draw2d::sprite::rotation const _rot
)
{
	for(
		part_unique_ptr const &cur_part
		:
		parts_
	)
		cur_part->orientation(
			_rot
		);
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sanguis::client::draw2d::sprite::rotation const _rot,
	sanguis::client::draw2d::sprite::index const _index
)
{
	parts_.at(
		_index.get()
	)->orientation(
		_rot
	);
}

bool
sanguis::client::draw2d::entities::model::object::dead() const
{
	return
		decay_time_.has_value();
}

void
sanguis::client::draw2d::entities::model::object::pause(
	bool const _value
)
{
	for(
		part_unique_ptr const &cur_part
		:
		parts_
	)
		cur_part->pause(
			_value
		);
}

bool
sanguis::client::draw2d::entities::model::object::is_decayed() const
{
	return
		this->animations_ended()
		&&
		fcppt::maybe(
			decay_time_,
			fcppt::const_(
				false
			),
			[](
				sanguis::client::draw2d::entities::model::decay_time const &_decay_time
			)
			{
				return
					_decay_time.ended();
			}
		);
}

void
sanguis::client::draw2d::entities::model::object::on_die()
{
	decay_time_ =
		optional_decay_time(
			sanguis::client::draw2d::entities::model::decay_time{
				diff_clock_,
				decay_option_
				==
				sanguis::client::draw2d::entities::model::decay_option::delayed
				?
					sanguis::duration_second(
						10
					)
				:
					sanguis::duration_second(
						0
					)
			}
		);

	health_pair_ =
		sanguis::client::optional_health_pair();

	this->change_animation();

	this->speed(
		sanguis::client::draw2d::speed(
			sanguis::client::draw2d::speed::value_type::null()
		)
	);
}

void
sanguis::client::draw2d::entities::model::object::speed(
	sanguis::client::draw2d::speed const &_speed
)
{
	sanguis::client::draw2d::speed const old_speed(
		this->speed()
	);

	sanguis::client::draw2d::entities::container::speed(
		_speed
	);

	if(
		sanguis::client::draw2d::speed_is_null(
			_speed
		)
		!=
		sanguis::client::draw2d::speed_is_null(
			old_speed
		)
	)
		this->change_animation();
}

sanguis::client::draw2d::entities::model::part &
sanguis::client::draw2d::entities::model::object::part(
	sanguis::client::draw2d::sprite::index const &_idx
)
{
	return
		*parts_.at(
			_idx.get()
		);
}

bool
sanguis::client::draw2d::entities::model::object::walking() const
{
	return
		!sanguis::client::draw2d::speed_is_null(
			this->speed()
		);
}

void
sanguis::client::draw2d::entities::model::object::health(
	sanguis::client::health const _health
)
{
	if(
		!sanguis::client::health_valid(
			_health
		)
	)
		health_pair_ =
			sanguis::client::optional_health_pair();

	fcppt::maybe_void(
		health_pair_,
		[
			_health
		](
			sanguis::client::health_pair &_health_pair
		)
		{
			_health_pair.health(
				_health
			);
		}
	);
}

void
sanguis::client::draw2d::entities::model::object::max_health(
	sanguis::client::max_health const _max_health
)
{
	fcppt::maybe_void(
		health_pair_,
		[
			_max_health
		](
			sanguis::client::health_pair &_health_pair
		)
		{
			_health_pair.max_health(
				_max_health
			);
		}
	);
}

sanguis::client::optional_health_pair const
sanguis::client::draw2d::entities::model::object::health_pair() const
{
	return
		health_pair_;
}

sanguis::client::draw2d::entities::model::object::object(
	sanguis::client::draw2d::entities::model::parameters const &_parameters,
	sanguis::client::load::model::object const &_model
)
:
	sanguis::client::draw2d::entities::container(
		_parameters.load_parameters().diff_clock(),
		_parameters.load_parameters().normal_system(),
		sanguis::client::draw2d::entities::model::expand_orders(
			_parameters.orders(),
			_model.size()
		),
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::sprite::dim,
			fcppt::cast::size_fun
		>(
			fcppt::math::dim::to_signed(
				_model.cell_size().get()
			)
		),
		_parameters.color()
	),
	sanguis::client::draw2d::entities::ifaces::with_health(),
	sanguis::client::draw2d::entities::ifaces::with_weapon(),
	diff_clock_(
		_parameters.load_parameters().diff_clock()
	),
	weapon_status_(
		sanguis::weapon_status::nothing
	),
	health_pair_{
		fcppt::optional_bind(
			_parameters.health_pair(),
			[](
				sanguis::client::health_pair const &_health_pair
			)
			{
				return
					sanguis::client::health_valid(
						_health_pair.health()
					)
					?
						sanguis::client::optional_health_pair{
							_health_pair
						}
					:
						sanguis::client::optional_health_pair{}
					;
			}
		)
	},
	decay_time_(),
	decay_option_(
		_parameters.decay_option()
	),
	parts_(
		fcppt::algorithm::map<
			part_vector
		>(
			boost::range::combine(
				fcppt::make_int_range_count(
					_model.size()
				),
				_model
			),
			[
				&_parameters,
				this
			](
				boost::tuple<
					part_vector::size_type,
					sanguis::client::load::model::part_map::value_type const &
				> const _arg
			)
			{
				return
					fcppt::make_unique_ptr_fcppt<
						sanguis::client::draw2d::entities::model::part
					>(
						diff_clock_,
						_parameters.load_parameters().sound_manager(),
						*boost::get<
							1
						>(
							_arg
						).second,
						this->at(
							sanguis::client::draw2d::sprite::index(
								fcppt::cast::size<
									sanguis::client::draw2d::sprite::index::value_type
								>(
									boost::get<
										0
									>(
										_arg
									)
								)
							)
						)
					);
			}
		)
	)
{
	this->change_animation(
		sanguis::client::load::animation_type::deploying
	);
}

void
sanguis::client::draw2d::entities::model::object::weapon(
	sanguis::optional_primary_weapon_type const _weapon
)
{
	for(
		part_unique_ptr const &cur_part
		:
		parts_
	)
		cur_part->weapon(
			_weapon
		);

	this->change_animation();
}

void
sanguis::client::draw2d::entities::model::object::weapon_status(
	sanguis::weapon_status const _weapon_status
)
{
	weapon_status_ =
		_weapon_status;

	this->change_animation();
}

void
sanguis::client::draw2d::entities::model::object::change_animation()
{
	this->change_animation(
		this->animation()
	);
}

void
sanguis::client::draw2d::entities::model::object::change_animation(
	sanguis::client::load::animation_type const _anim
)
{
	for(
		part_unique_ptr const &cur_part
		:
		parts_
	)
	{
		sanguis::client::load::animation_type part_anim(
			_anim
		);

		while(
			!cur_part->try_animation(
				part_anim
			)
		)
			part_anim =
				this->fallback_anim(
					part_anim
				);
	}
}

sanguis::client::load::animation_type
sanguis::client::draw2d::entities::model::object::fallback_anim(
	sanguis::client::load::animation_type const _anim
) const
{
	switch(
		_anim
	)
	{
	case sanguis::client::load::animation_type::none:
		FCPPT_ASSERT_UNREACHABLE_MESSAGE(
			FCPPT_TEXT("None animation not available!")
		);
		break;
	case sanguis::client::load::animation_type::attacking:
	case sanguis::client::load::animation_type::reloading:
		return
			this->walking()
			?
				sanguis::client::load::animation_type::walking
			:
				sanguis::client::load::animation_type::none
			;
	case sanguis::client::load::animation_type::deploying:
	case sanguis::client::load::animation_type::walking:
	case sanguis::client::load::animation_type::dying:
		return
			sanguis::client::load::animation_type::none;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sanguis::client::load::animation_type
sanguis::client::draw2d::entities::model::object::animation() const
{
	return
		this->dead()
		?
			sanguis::client::load::animation_type::dying
		:
			weapon_status_
			==
			sanguis::weapon_status::reloading
			?
				sanguis::client::load::animation_type::reloading
			:
				weapon_status_
				==
				sanguis::weapon_status::attacking
				?
					sanguis::client::load::animation_type::attacking
				:
					this->walking()
					?
						sanguis::client::load::animation_type::walking
					:
						sanguis::client::load::animation_type::none
					;
}

bool
sanguis::client::draw2d::entities::model::object::animations_ended() const
{
	if(
		this->animation()
		!=
		sanguis::client::load::animation_type::dying
	)
		return
			true;

	// TODO: all_of?
	for(
		auto const &cur_part
		:
		parts_
	)
		if(
			!cur_part->ended()
		)
			return
				false;
	return
		true;
}
