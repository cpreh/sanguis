#include <sanguis/client/draw2d/log_location.hpp>
#include <sanguis/client/draw2d/speed_is_null.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/part.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/decay_time.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/load/model/collection.hpp>
#include <sanguis/load/model/object.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/weapon_type.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
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
	model::parameters const &_param,
	fcppt::string const &_name,
	entities::order_vector const &_orders,
	needs_healthbar::type const _needs_healthbar,
	decay_option::type const _decay_option
)
:
	container(
		_param.diff_clock(),
		_param.normal_system(),
		expand_orders(
			_orders,
			_param.collection()[_name].size()
		),
		fcppt::math::dim::structure_cast<
			sprite::dim
		>(
			_param.collection()[_name].dim()
		)
	),
	with_health(),
	with_weapon(),
	diff_clock_(
		_param.diff_clock()
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
		_needs_healthbar == needs_healthbar::yes
		?
			fcppt::make_unique_ptr<
				model::healthbar
			>(
				_param.colored_system()
			)
		:
			std::unique_ptr<
				model::healthbar
			>()
	),
	decay_time_(),
	decay_option_(_decay_option),
	parts_()
{
	part_vector::size_type index(0);

	load::model::object const &model(
		_param.collection()[_name]
	);

	for(
		load::model::object::const_iterator it(
			model.begin()
		);
		it != model.end();
		++it
	)
		fcppt::container::ptr::push_back_unique_ptr(
			parts_,
			fcppt::make_unique_ptr<
				model::part
			>(
				diff_clock_,
				*it->second,
				this->at(
					sprite::index(
						index++
					)
				)
			)
		);

	this->change_animation(
		animation_type::deploying
	);
}

sanguis::client::draw2d::entities::model::object::~object()
{
}

sanguis::client::health const
sanguis::client::draw2d::entities::model::object::max_health() const
{
	return max_health_;
}

sanguis::client::health const
sanguis::client::draw2d::entities::model::object::health() const
{
	return health_;
}

void
sanguis::client::draw2d::entities::model::object::update()
{
	container::update();

	if(
		healthbar_
	)
		healthbar_->attach_to(
			this->master().pos(),
			this->master().size()
		);

	for(
		part_vector::iterator it(
			parts_.begin()
		);
		it != parts_.end();
		++it
	)
		it->update();
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sprite::rotation const _rot
)
{
	for(
		part_vector::iterator it(
			parts_.begin()
		);
		it != parts_.end();
		++it
	)
		it->orientation(
			_rot
		);
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sprite::rotation const _rot,
	sprite::index const _index
)
{
	parts_.at(
		_index.get()
	).orientation(
		_rot
	);
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
sanguis::client::draw2d::entities::model::object::on_decay()
{
	decay_time_.take(
		fcppt::make_unique_ptr<
			model::decay_time
		>(
			diff_clock_,
			decay_option_ == decay_option::delayed
			?
				sanguis::duration_second(10)
			:
				sanguis::duration_second(0)
		)
	);

	healthbar_.reset();

	this->change_animation();

	this->speed(
		draw2d::speed(
			draw2d::speed::value_type::null()
		)
	);
}

void
sanguis::client::draw2d::entities::model::object::speed(
	draw2d::speed const &_speed
)
{
	draw2d::speed const old_speed(
		this->speed()
	);

	container::speed(
		_speed
	);

	if(
		draw2d::speed_is_null(
			_speed
		)
		!=
		draw2d::speed_is_null(
			old_speed
		)
	)
		this->change_animation();
}

sanguis::client::draw2d::entities::model::part &
sanguis::client::draw2d::entities::model::object::part(
	sprite::index const &_idx
)
{
	return
		parts_.at(
			_idx.get()
		);
}

bool
sanguis::client::draw2d::entities::model::object::dead() const
{
	return
		decay_time_.get() != nullptr;
}

bool
sanguis::client::draw2d::entities::model::object::walking() const
{
	return
		!draw2d::speed_is_null(
			this->speed()
		);
}

bool
sanguis::client::draw2d::entities::model::object::has_health() const
{
	return
		this->max_health().get() > 0;
}

void
sanguis::client::draw2d::entities::model::object::health(
	client::health const _health
)
{
	health_ = _health;

	this->update_healthbar();
}

void
sanguis::client::draw2d::entities::model::object::max_health(
	client::health const _max_health
)
{
	max_health_ = _max_health;

	this->update_healthbar();
}

void
sanguis::client::draw2d::entities::model::object::weapon(
	sanguis::weapon_type const _weapon
)
{
	for(
		part_vector::iterator it(
			parts_.begin()
		);
		it != parts_.end();
		++it
	)
		it->weapon(
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
			fcppt::log::_ << FCPPT_TEXT("attacking(): value already set!")
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
			fcppt::log::_ << FCPPT_TEXT("reloading(): value already set!")
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
	animation_type::type const _anim
)
{
	for(
		part_vector::iterator it(
			parts_.begin()
		);
		it != parts_.end();
		++it
	)
	{
		animation_type::type part_anim(
			_anim
		);

		while(
			!it->try_animation(
				part_anim
			)
		)
			part_anim =
				this->fallback_anim(
					part_anim
				);
	}
}

sanguis::animation_type::type
sanguis::client::draw2d::entities::model::object::fallback_anim(
	animation_type::type const _anim
) const
{
	switch(
		_anim
	)
	{
	case animation_type::none:
		return animation_type::size;
	case animation_type::attacking:
	case animation_type::reloading:
		return
			this->walking()
			?
				animation_type::walking
			:
				animation_type::none;
	case animation_type::deploying:
	case animation_type::walking:
	case animation_type::dying:
		return animation_type::none;
	case animation_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sanguis::animation_type::type
sanguis::client::draw2d::entities::model::object::animation() const
{
	return
		this->dead()
		?
			animation_type::dying
		:
			reloading_
			?
				animation_type::reloading
			:
				attacking_
				?
					animation_type::attacking
				:
					this->walking()
					?
						animation_type::walking
					:
						animation_type::none;
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
	for(
		part_vector::const_iterator it(
			parts_.begin()
		);
		it != parts_.end();
		++it
	)
		if(
			!it->ended()
		)
			return false;
	return true;
}
