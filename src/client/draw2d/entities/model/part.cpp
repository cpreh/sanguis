#include "part.hpp"
#include "clamp_orientation.hpp"
#include "loop_method.hpp"
#include "orientation.hpp"
#include "sound_state.hpp"
#include "../../sprite/dim.hpp"
#include "../../sprite/rotation_type.hpp"
#include "../../../../load/model/part.hpp"
#include "../../../../load/model/base_animation_not_found.hpp"
#include "../../../../load/model/animation_context.hpp"
#include "../../../../load/model/weapon_category.hpp"
#include "../../../../load/model/animation.hpp"
#include <sge/sprite/animation/texture_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/ref.hpp>

sanguis::client::draw2d::entities::model::part::part(
	load::model::part const& _load_part,
	sprite::normal::object &_ref
)
:
	anim_diff_clock_(),
	desired_orientation_(),
	load_part_(
		_load_part
	),
	ref_(
		_ref
	),
	animation_type_(
		sanguis::animation_type::size
	),
	weapon_(
		weapon_type::none
	),
	sound_state_(),
	animation_context_(),
	animation_(),
	animation_ended_(
		false
	)
{
	ref_.size(
		sprite::dim::null()
	);
}

sanguis::client::draw2d::entities::model::part::~part()
{
}

bool
sanguis::client::draw2d::entities::model::part::try_animation(
	animation_type::type const _atype
)
{
	// WHY?
	if(
		weapon_ == weapon_type::size
	)
		weapon_ = weapon_type::none;
	
	if(
		animation_type_ == _atype
	)
		return true;
	
	if(
		!load_part_[
			weapon_
		].has_animation(
			_atype
		)
	)
		return false;

	this->load_animation(
		_atype
	);

	animation_type_ = _atype;

	return true;
}

void
sanguis::client::draw2d::entities::model::part::weapon(
	weapon_type::type const _weapon
)
{
	// we lose the animation here
	// which model has to reset
	weapon_ = _weapon;

	animation_type_ = sanguis::animation_type::size;

	sound_state_.reset();
}

void
sanguis::client::draw2d::entities::model::part::update(
	time_type const _time
)
{
	anim_diff_clock_.update(
		_time
	);
	
	if(
		!animation_ && animation_context_
	)
	{
		animation_context_->update();

		if(
			animation_context_->is_finished()
		)
		{
			animation_.take(
				fcppt::make_unique_ptr<
					sprite::normal::texture_animation
				>(
					animation_context_->result(),
					model::loop_method(
						animation_type_
					),
					fcppt::ref(
						ref_
					),
					anim_diff_clock_.callback()
				)
			);

			ref_.size(
				fcppt::math::dim::structure_cast<
					sprite::dim
				>(
					animation_->series().begin()->dim()
				)
			);
		}
	}
	
	if(
		sound_state_
	) 
		sound_state_->update(
			this->object().pos()
		);

	if(
		animation_
	)
		animation_ended_ = animation_->process() || animation_ended_;

	if(
		!desired_orientation_
	)
		return;
	
	if(
		fcppt::math::compare(
			this->orientation(),
			*desired_orientation_
		)
	)
		return;

	this->update_orientation(
		model::orientation(
			_time,
			this->orientation(),
			*desired_orientation_
		)
	);
}

void
sanguis::client::draw2d::entities::model::part::orientation(
	sprite::rotation_type _rot
)
{
	_rot =
		model::clamp_orientation(
			_rot
		);

	if(
		!desired_orientation_
	)
		this->update_orientation(
			_rot
		);

	desired_orientation_ = _rot;
}

bool
sanguis::client::draw2d::entities::model::part::ended() const
{
	return animation_ended_;
}

sanguis::client::draw2d::sprite::normal::object &
sanguis::client::draw2d::entities::model::part::object()
{
	return ref_;
}

sanguis::client::draw2d::sprite::normal::object const &
sanguis::client::draw2d::entities::model::part::object() const
{
	return ref_;
}

void
sanguis::client::draw2d::entities::model::part::load_animation(
	animation_type::type const _atype
)
{
	animation_.reset();

	animation_context_.take(
		load_part_[
			weapon_
		][
			_atype
		].load()
	);

	if(
		sound_state_
	)
		sound_state_->stop();
	
	sound_state_.take(
		fcppt::make_unique_ptr<
			model::sound_state
		>(
			load_part_[
				weapon_
			]
			[
				_atype
			].sounds()
		)
	);
}

void
sanguis::client::draw2d::entities::model::part::update_orientation(
	sprite::rotation_type const _rot
)
{
	ref_.rotation(
		_rot
	);
}

sanguis::client::draw2d::sprite::rotation_type
sanguis::client::draw2d::entities::model::part::orientation() const
{
	return ref_.rotation();
}
