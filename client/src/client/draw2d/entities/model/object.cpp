#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/health_valid.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/speed_is_null.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time.hpp>
#include <sanguis/client/draw2d/entities/model/expand_orders.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
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
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assert/unreachable_message.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::model::object::object(
	sanguis::client::draw2d::entities::model::parameters const &_parameters
)
:
	sanguis::client::draw2d::entities::container(
		_parameters.load_parameters().diff_clock(),
		_parameters.load_parameters().normal_system(),
		sanguis::client::draw2d::entities::model::expand_orders(
			_parameters.orders(),
			_parameters.load_parameters().collection()[
				_parameters.name().get()
			].size()
		),
		fcppt::math::dim::structure_cast<
			sanguis::client::draw2d::sprite::dim
		>(
			_parameters.load_parameters().collection()[
				_parameters.name().get()
			].cell_size().get()
		)
	),
	sanguis::client::draw2d::entities::ifaces::with_health(),
	sanguis::client::draw2d::entities::ifaces::with_weapon(),
	diff_clock_(
		_parameters.load_parameters().diff_clock()
	),
	weapon_status_(
		sanguis::weapon_status::nothing
	),
	healthbar_(
		_parameters.health_pair()
		&&
		sanguis::client::health_valid(
			_parameters.health_pair()->health()
		)
		?
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::model::healthbar
			>(
				_parameters.load_parameters().colored_system(),
				*_parameters.health_pair()
			)
		:
			std::unique_ptr<
				sanguis::client::draw2d::entities::model::healthbar
			>()
	),
	decay_time_(),
	decay_option_(
		_parameters.decay_option()
	),
	parts_()
{
	sanguis::client::load::model::object const &model(
		_parameters.load_parameters().collection()[
			_parameters.name().get()
		]
	);

	part_vector::size_type index(
		0u
	);

	for(
		auto const &cur_part
		:
		model
	)
		fcppt::container::ptr::push_back_unique_ptr(
			parts_,
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::model::part
			>(
				diff_clock_,
				_parameters.load_parameters().sound_manager(),
				*cur_part.second,
				this->at(
					sanguis::client::draw2d::sprite::index(
						fcppt::cast::size<
							sanguis::client::draw2d::sprite::index::value_type
						>(
							index++
						)
					)
				)
			)
		);

	this->change_animation(
		sanguis::client::load::animation_type::deploying
	);
}

sanguis::client::draw2d::entities::model::object::~object()
{
}

void
sanguis::client::draw2d::entities::model::object::update()
{
	sanguis::client::draw2d::entities::container::update();

	if(
		healthbar_
	)
		healthbar_->attach_to(
			this->master().pos(),
			this->master().size()
		);

	for(
		auto &cur_part
		:
		parts_
	)
		cur_part.update();
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sanguis::client::draw2d::sprite::rotation const _rot
)
{
	for(
		auto &cur_part
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
	parts_.at(
		_index.get()
	).orientation(
		_rot
	);
}

bool
sanguis::client::draw2d::entities::model::object::dead() const
{
	return
		decay_time_.get() != nullptr;
}

void
sanguis::client::draw2d::entities::model::object::pause(
	bool const _value
)
{
	for(
		auto &cur_part
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
		decay_time_
		&&
		decay_time_->ended();
}

void
sanguis::client::draw2d::entities::model::object::on_die()
{
	decay_time_ =
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::entities::model::decay_time
		>(
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
		);

	healthbar_.reset();

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
		healthbar_.reset();

	if(
		healthbar_
	)
		healthbar_->health(
			_health
		);
}

void
sanguis::client::draw2d::entities::model::object::max_health(
	sanguis::client::max_health const _max_health
)
{
	if(
		healthbar_
	)
		healthbar_->max_health(
			_max_health
		);
}

sanguis::client::optional_health_pair const
sanguis::client::draw2d::entities::model::object::health_pair() const
{
	return
		healthbar_
		?
			sanguis::client::optional_health_pair(
				healthbar_->health_pair()
			)
		:
			sanguis::client::optional_health_pair()
		;
}

void
sanguis::client::draw2d::entities::model::object::weapon(
	sanguis::optional_primary_weapon_type const _weapon
)
{
	for(
		auto &cur_part
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
		auto &cur_part
		:
		parts_
	)
	{
		sanguis::client::load::animation_type part_anim(
			_anim
		);

		while(
			!cur_part.try_animation(
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
		return true;

	for(
		auto const &cur_part
		:
		parts_
	)
		if(
			!cur_part.ended()
		)
			return false;
	return true;
}
