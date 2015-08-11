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
#include <sanguis/client/draw2d/entities/level.hpp>
#include <sanguis/client/draw2d/entities/level_vector.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/entities/model/part.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/load/animation_type.hpp>
#include <sanguis/client/load/model/collection.hpp>
#include <sanguis/client/load/model/object.hpp>
#include <sanguis/client/load/model/part_fwd.hpp>
#include <sanguis/client/load/model/part_map.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/algorithm/all_of.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_signed.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
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
		sanguis::client::draw2d::sprite::index const index
		:
		fcppt::make_int_range_count(
			fcppt::strong_typedef_construct_cast<
				sanguis::client::draw2d::sprite::index,
				fcppt::cast::size_fun
			>(
				parts_.size()
			)
		)
	)
		this->part(
			index
		).update(
			this->at(
				index
			)
		);
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sanguis::client::draw2d::sprite::rotation const _rot
)
{
	for(
		sanguis::client::draw2d::entities::model::part &cur_part
		:
		parts_
	)
		cur_part.orientation(
			_rot
		);
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sanguis::client::draw2d::sprite::rotation const _rot,
	sanguis::client::draw2d::sprite::index const _index
)
{
	this->part(
		_index
	).orientation(
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
		sanguis::client::draw2d::entities::model::part &cur_part
		:
		parts_
	)
		cur_part.pause(
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
		parts_.at(
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
	sanguis::client::draw2d::entities::model::object::object(
		_parameters,
		_model,
		fcppt::algorithm::map<
			part_vector
		>(
			_model,
			[
				&_parameters
			](
				sanguis::client::load::model::part_map::value_type const &_part
			)
			{
				return
					sanguis::client::draw2d::entities::model::part{
						_parameters.load_parameters().diff_clock(),
						_parameters.load_parameters().sound_manager(),
						*_part.second,
						_parameters.primary_weapon_type(),
						_parameters.rotation(),
						// FIXME: This does not work right now
						sanguis::client::load::animation_type::deploying
					};
			}
		)
	)
{
}

sanguis::client::draw2d::entities::model::object::object(
	sanguis::client::draw2d::entities::model::parameters const &_parameters,
	sanguis::client::load::model::object const &_model,
	part_vector &&_parts
)
:
	sanguis::client::draw2d::entities::container(
		_parameters.load_parameters().diff_clock(),
		_parameters.load_parameters().normal_system(),
		fcppt::algorithm::map<
			sanguis::client::draw2d::entities::level_vector
		>(
			fcppt::make_int_range_count(
				fcppt::strong_typedef_construct_cast<
					sanguis::client::draw2d::sprite::index,
					fcppt::cast::size_fun
				>(
					_model.size()
				)
			),
			[
				&_parameters,
				&_parts
			](
				sanguis::client::draw2d::sprite::index const _index
			)
			{
				return
					sanguis::client::draw2d::entities::level{
						_parameters.order_function()(
							_index
						),
						_parts[
							_index.get()
						].texture()
					};
			}
		),
		_parameters.speed(),
		_parameters.center(),
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::sprite::dim,
			fcppt::cast::size_fun
		>(
			fcppt::math::dim::to_signed(
				_model.cell_size().get()
			)
		),
		_parameters.rotation(),
		_parameters.color()
	),
	sanguis::client::draw2d::entities::ifaces::with_health(),
	sanguis::client::draw2d::entities::ifaces::with_weapon(),
	diff_clock_(
		_parameters.load_parameters().diff_clock()
	),
	weapon_status_(
		_parameters.weapon_status()
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
		std::move(
			_parts
		)
	)
{
	// TODO: Remove this when deploying actually works
	this->change_animation();
}

void
sanguis::client::draw2d::entities::model::object::weapon(
	sanguis::optional_primary_weapon_type const _weapon
)
{
	for(
		sanguis::client::draw2d::entities::model::part &cur_part
		:
		parts_
	)
		cur_part.weapon(
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
		sanguis::client::draw2d::entities::model::part &cur_part
		:
		parts_
	)
		cur_part.animation(
			_anim
		);
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
				this->walking()
				?
					sanguis::client::load::animation_type::walking
				:
					weapon_status_
					==
					sanguis::weapon_status::attacking
					?
						sanguis::client::load::animation_type::attacking
					:
						sanguis::client::load::animation_type::none
					;
}

bool
sanguis::client::draw2d::entities::model::object::animations_ended() const
{
	return
		this->animation()
		!=
		sanguis::client::load::animation_type::dying
		||
		fcppt::algorithm::all_of(
			parts_,
			[](
				sanguis::client::draw2d::entities::model::part const &_part
			)
			{
				return
					_part.ended();
			}
		);
}
