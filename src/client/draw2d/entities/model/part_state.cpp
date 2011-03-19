#include "part_state.hpp"
#include "part.hpp"
#include "../../../../load/model/animation.hpp"
#include "../../../../load/model/part.hpp"
#include "../../../../load/model/animation_sound.hpp"
#include "../../../../load/model/weapon_category.hpp"
#include "../../../../animation_sound_type.hpp"
#include <sge/sprite/object_impl.hpp>
#include <sge/audio/sound/positional.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

// TODO: hier animationskram rausnehmen, ggf. friend-Beziehung wegnehmen
sanguis::client::draw2d::entities::model::part_state::part_state(
	load::model::part const &_part,
	part &_ref,
	animation_type::type const _animation_type,
	weapon_type::type const _weapon_type
)
:
	ref_(_ref),
	anim_(
		_part[
			_weapon_type
		][
			_animation_type
		]
	),
	sstart_(
		anim_.sounds()[
			animation_sound_type::start
		]
	),
	srunning_(
		anim_.sounds()[
			animation_sound_type::running
		]
	),
	send_(
		anim_.sounds()[
			animation_sound_type::end
		]
	),
	animation_type_(_animation_type),
	weapon_type_(_weapon_type),
	start_played_(false)
{
	this->init_sound(
		sstart_
	);

	this->init_sound(
		srunning_
	);

	this->init_sound(
		send_
	);

	this->update_sounds();

	this->play(
		sstart_
	);
}

sanguis::animation_type::type
sanguis::client::draw2d::entities::model::part_state::animation_type() const
{
	return animation_type_;
}

sanguis::weapon_type::type
sanguis::client::draw2d::entities::model::part_state::weapon_type() const
{
	return weapon_type_;
}

void
sanguis::client::draw2d::entities::model::part_state::update()
{
	this->update_sounds();

	if(
		!sstart_ || 
		(!start_played_ && 
		sstart_->status() == sge::audio::sound::play_status::stopped)
	)
	{
		start_played_ = true;

		this->play(
			srunning_,
			sge::audio::sound::repeat::loop
		);
	}
}

sanguis::client::draw2d::entities::model::part_state::~part_state()
{
	this->play(
		send_
	);
}

void
sanguis::client::draw2d::entities::model::part_state::play(
	sge::audio::sound::positional_ptr const _sound,
	sge::audio::sound::repeat::type const _type
)
{
	if(
		_type
	)
		_sound->play(
			_type
		);
}

void
sanguis::client::draw2d::entities::model::part_state::update_sound(
	sge::audio::sound::positional_ptr const _sound
)
{
	if(
		_sound
	)
		_sound->position(
			sge::audio::vector(
				static_cast<
					sge::audio::scalar
				>(
					ref_.object().pos().x()
				),
				static_cast<
					sge::audio::scalar
				>(
					0
				),
				static_cast<
					sge::audio::scalar
				>(
					ref_.object().pos().y()
				)
			)
		);
}

void
sanguis::client::draw2d::entities::model::part_state::init_sound(
	sge::audio::sound::positional_ptr const _sound
)
{
	if(
		!_sound
	)
		return;
	// TODO!
#if 0
	s->positional(true);
	s->rolloff(
		static_cast<sge::audio::scalar>(1)
		/ static_cast<sge::audio::scalar>(
			resolution().h()
		)
	);
#endif
}

void
sanguis::client::draw2d::entities::model::part_state::update_sounds()
{
	this->update_sound(
		sstart_
	);

	this->update_sound(
		srunning_
	);

	this->update_sound(
		send_
	);
}
