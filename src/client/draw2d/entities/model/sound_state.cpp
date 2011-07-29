#include "sound_state.hpp"
#include "../../../../load/model/animation/sound.hpp"
#include "../../../../animation_sound_type.hpp"
#include <sge/sprite/object_impl.hpp>
#include <sge/audio/sound/positional.hpp>
#include <fcppt/assign/make_array.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sanguis::client::draw2d::entities::model::sound_state::sound_state(
	load::model::animation::sound const &_sounds
)
:
	sounds_(
		fcppt::assign::make_array(
			_sounds[
				animation_sound_type::start
			]
		)
		(
			_sounds[
				animation_sound_type::middle
			]
		)
	),
	current_sound_index_(
		sanguis::animation_sound_type::start
	)
{
	this->play(
		sge::audio::sound::repeat::once
	);
}

void
sanguis::client::draw2d::entities::model::sound_state::update(
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
sanguis::client::draw2d::entities::model::sound_state::stop()
{
	if(
		this->current_sound()
	)
		this->current_sound()->stop();
}

sanguis::client::draw2d::entities::model::sound_state::~sound_state()
{
}

void
sanguis::client::draw2d::entities::model::sound_state::play(
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
sanguis::client::draw2d::entities::model::sound_state::current_sound() const
{
	return
		sounds_[
			current_sound_index_
		];
}
