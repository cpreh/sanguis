#include "object.hpp"
#include "part.hpp"
#include "parameters.hpp"
#include "healthbar.hpp"
#include "decay_time.hpp"
#include "../../log.hpp"
#include "../../sprite/index.hpp"
#include "../../../../load/model/collection.hpp"
#include "../../../../load/model/object.hpp"
#include "../../../../exception.hpp"
#include <sge/sprite/object_impl.hpp>
#include <sge/time/second.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <ostream>

sanguis::client::draw2d::entities::model::object::object(
	model::parameters const &_param,
	fcppt::string const &_name,
	sprite::order const _order,
	needs_healthbar::type const _needs_healthbar,
	decay_option::type const _decay_option
)
:
	container(
		_param.normal_system(),
		_param.collection()[_name].size(),
		_order,
		fcppt::math::dim::structure_cast<
			sprite::dim
		>(
			_param.collection()[_name].dim()
		)
	),
	with_health(),
	with_weapon(),
	attacking_(false),
	reloading_(false),
	health_(0),
	max_health_(0),
	healthbar_(
		_needs_healthbar == needs_healthbar::yes
		?
			fcppt::make_unique_ptr<
				model::healthbar
			>(
				fcppt::ref(
					_param.colored_system()
				)
			)
		:
			fcppt::unique_ptr<
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
				*it->second,
				fcppt::ref(
					this->at(
						sprite::index(
							index++
						)
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
sanguis::client::draw2d::entities::model::object::update(
	time_type const _time
)
{
	container::update(
		_time
	);

	if(
		healthbar_
	)
		healthbar_->attach_to(
			this->master().pos(),
			this->master().size()
		);
	
	if(
		decay_time_
	)
		decay_time_->update(
			_time
		);

	BOOST_FOREACH(
		model::part &cur_part,
		parts_
	)
		cur_part.update(
			_time
		);
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sprite::rotation_type const _rot
)
{
	BOOST_FOREACH(
		model::part &cur_part,
		parts_
	)
		cur_part.orientation(
			_rot
		);
}

void
sanguis::client::draw2d::entities::model::object::orientation(
	sprite::rotation_type const _rot,
	size_type const _index
)
{
	parts_.at(
		_index
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
			decay_option_ == decay_option::delayed
			?
				sge::time::second(10)
			:
				sge::time::second(0)
		)
	);

	healthbar_.reset();

	this->change_animation();

	this->speed(
		draw2d::speed(
			draw2d::speed::value_type::null()
		)
	); // FIXME
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
		fcppt::math::vector::is_null(
			_speed.get()
		)
		!=
		fcppt::math::vector::is_null(
			old_speed.get()
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
		decay_time_ != 0;
}

bool
sanguis::client::draw2d::entities::model::object::walking() const
{
	return
		!fcppt::math::vector::is_null(
			this->speed().get()
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
	weapon_type::type const _weapon
)
{
	BOOST_FOREACH(
		model::part &cur_part,
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
			object::log(),
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
			object::log(),
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
	BOOST_FOREACH(
		model::part &cur_part,
		parts_
	)
	{
		animation_type::type part_anim(
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

	throw sanguis::exception(
		FCPPT_TEXT("Invalid animation in fallback_anim!")
	);
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

fcppt::log::object &
sanguis::client::draw2d::entities::model::object::log()
{
	static fcppt::log::object logger(
		fcppt::log::parameters::inherited(
			draw2d::log(),
			FCPPT_TEXT("model")
		)
	);

	return logger;
}
