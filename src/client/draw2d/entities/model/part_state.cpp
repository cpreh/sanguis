#include "part_state.hpp"
#include "../../../../load/model/animation.hpp"
#include "../../../../load/model/part.hpp"
#include "../../../../load/model/animation_sound.hpp"
#include "../../../../load/model/weapon_category.hpp"
#include "../../../../animation_sound_type.hpp"
#include <sge/sprite/object_impl.hpp>
#include <sge/audio/sound/positional.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sanguis::client::draw2d::entities::model::part_state::part_state(
	load::model::part const &_part,
	animation_type::type const _animation_type,
	weapon_type::type const _weapon_type
)
:
	anim_(
		_part[
			_weapon_type
		][
			_animation_type
		]
	),
	sounds_(
		fcppt::assign::make_array(
			anim_.sounds()[
				animation_sound_type::start
			]
		)
		(
			anim_.sounds()[
				animation_sound_type::middle
			]
		)
	),
	current_sound_index_(
		sanguis::animation_sound_type::start
	),
	animation_type_(_animation_type)
{
	this->play(
		sge::audio::sound::repeat::once
	);
}

sanguis::animation_type::type
sanguis::client::draw2d::entities::model::part_state::animation_type() const
{
	return animation_type_;
}

void
sanguis::client::draw2d::entities::model::part_state::update(
	draw2d::sprite::point const &_pos
)
{
	if(
		!this->current_sound()
		||
		(
			current_sound_index_ == animation_sound_type::start
			&&
			this->current_sound()->status() == sge::audio::sound::play_status::stopped
		)
	)
	{
		current_sound_index_ = animation_sound_type::middle;

		this->play(
			sge::audio::sound::repeat::loop
		);
	}

	if(
		!this->current_sound()
	)
		return;

	this->current_sound()->position(
		sge::audio::vector(
			static_cast<
				sge::audio::scalar
			>(
				_pos.x()
			),
			static_cast<
				sge::audio::scalar
			>(
				0
			),
			static_cast<
				sge::audio::scalar
			>(
				_pos.y()
			)
		)
	);

	this->current_sound()->update();
}

void
sanguis::client::draw2d::entities::model::part_state::stop()
{
	if(
		this->current_sound()
	)
		this->current_sound()->stop();
}

sanguis::client::draw2d::entities::model::part_state::~part_state()
{
}

void
sanguis::client::draw2d::entities::model::part_state::play(
	sge::audio::sound::repeat::type const _type
)
{
	if(
		!this->current_sound()
	)
		return;

	this->current_sound()->play(
		_type
	);
}

sge::audio::sound::positional_ptr const
sanguis::client::draw2d::entities::model::part_state::current_sound() const
{
	return
		sounds_[
			current_sound_index_
		];
}
