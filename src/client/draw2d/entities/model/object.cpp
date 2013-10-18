#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/draw2d/log_location.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/speed_is_null.hpp>
#include <sanguis/client/draw2d/entities/container.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_health.hpp>
#include <sanguis/client/draw2d/entities/ifaces/with_weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/entities/model/part.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/object.hpp>
#include <sanguis/load/animation_type.hpp>
#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/object.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/assert/unreachable_message.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::client::draw2d::log_location()
		/
		FCPPT_TEXT("model")
	)
);

sanguis::client::draw2d::entities::order_vector const
expand_orders(
	sanguis::client::draw2d::entities::order_vector _orders,
	sanguis::load::model::object::size_type const _size
)
{
	FCPPT_ASSERT_PRE(
		!_orders.empty()
	);

	FCPPT_ASSERT_PRE(
		_orders.size()
		<=
		_size
	);

	_orders.resize(
		_size,
		_orders.back()
	);

	return _orders;
}

}

sanguis::client::draw2d::entities::model::object::object(
	sanguis::client::draw2d::entities::model::parameters const &_parameters
)
:
	sanguis::client::draw2d::entities::container(
		_parameters.load_parameters().diff_clock(),
		_parameters.load_parameters().normal_system(),
		expand_orders(
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
	attacking_(
		false
	),
	reloading_(
		false
	),
	health_(
		0.f
	),
	max_health_(
		0.f
	),
	healthbar_(
		_parameters.needs_healthbar()
		==
		sanguis::client::draw2d::entities::model::needs_healthbar::yes
		?
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::model::healthbar
			>(
				_parameters.load_parameters().colored_system()
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
	part_vector::size_type index(0);

	sanguis::load::model::object const &model(
		_parameters.load_parameters().collection()[
			_parameters.name().get()
		]
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
						index++
					)
				)
			)
		);

	this->change_animation(
		sanguis::load::animation_type::deploying
	);
}

sanguis::client::draw2d::entities::model::object::~object()
{
}

sanguis::client::max_health const
sanguis::client::draw2d::entities::model::object::max_health() const
{
	return
		max_health_;
}

sanguis::client::health const
sanguis::client::draw2d::entities::model::object::health() const
{
	return
		health_;
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

bool
sanguis::client::draw2d::entities::model::object::is_decayed() const
{
	return
		this->animations_ended()
		&& decay_time_
		&& decay_time_->ended();
}

void
sanguis::client::draw2d::entities::model::object::on_die()
{
	decay_time_.take(
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

bool
sanguis::client::draw2d::entities::model::object::has_health() const
{
	return
		this->max_health().get()
		>
		0;
}

void
sanguis::client::draw2d::entities::model::object::health(
	sanguis::client::health const _health
)
{
	health_ = _health;

	this->update_healthbar();
}

void
sanguis::client::draw2d::entities::model::object::max_health(
	sanguis::client::max_health const _max_health
)
{
	max_health_ = _max_health;

	this->update_healthbar();
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
sanguis::client::draw2d::entities::model::object::attacking(
	bool const _attacking
)
{
	if(
		_attacking == attacking_
	)
		FCPPT_LOG_WARNING(
			::logger,
			fcppt::log::_
				<< FCPPT_TEXT("attacking(): value already set!")
		);

	attacking_ = _attacking;

	this->change_animation();
}

void
sanguis::client::draw2d::entities::model::object::reloading(
	bool const _reloading
)
{
	if(
		_reloading == reloading_
	)
		FCPPT_LOG_WARNING(
			::logger,
			fcppt::log::_
				<< FCPPT_TEXT("reloading(): value already set!")
		);

	reloading_ = _reloading;

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
	sanguis::load::animation_type const _anim
)
{
	for(
		auto &cur_part
		:
		parts_
	)
	{
		sanguis::load::animation_type part_anim(
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

sanguis::load::animation_type
sanguis::client::draw2d::entities::model::object::fallback_anim(
	sanguis::load::animation_type const _anim
) const
{
	switch(
		_anim
	)
	{
	case sanguis::load::animation_type::none:
		FCPPT_ASSERT_UNREACHABLE_MESSAGE(
			FCPPT_TEXT("None animation not available!")
		);
		break;
	case sanguis::load::animation_type::attacking:
	case sanguis::load::animation_type::reloading:
		return
			this->walking()
			?
				sanguis::load::animation_type::walking
			:
				sanguis::load::animation_type::none
			;
	case sanguis::load::animation_type::deploying:
	case sanguis::load::animation_type::walking:
	case sanguis::load::animation_type::dying:
		return
			sanguis::load::animation_type::none;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sanguis::load::animation_type
sanguis::client::draw2d::entities::model::object::animation() const
{
	return
		this->dead()
		?
			sanguis::load::animation_type::dying
		:
			reloading_
			?
				sanguis::load::animation_type::reloading
			:
				attacking_
				?
					sanguis::load::animation_type::attacking
				:
					this->walking()
					?
						sanguis::load::animation_type::walking
					:
						sanguis::load::animation_type::none
					;
}

void
sanguis::client::draw2d::entities::model::object::update_healthbar()
{
	if(
		!healthbar_
	)
		return;

	healthbar_->update_health(
		this->health(),
		this->max_health()
	);
}

bool
sanguis::client::draw2d::entities::model::object::animations_ended() const
{
	if(
		this->animation()
		!=
		sanguis::load::animation_type::dying
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
