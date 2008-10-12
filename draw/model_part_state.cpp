#include "model_part_state.hpp"
#include "../load/model/animation_sound.hpp"
#include "../animation_sound_type.hpp"
#include <sge/audio/sound.hpp>

sanguis::draw::model_part_state::model_part_state(
	load::model::part const &part_,
	animation_type::type const animation_type_,
	weapon_type::type const weapon_type_)
:
	anim_(part_[weapon_type_][animation_type_]),
	sstart(anim_.sounds()[animation_sound_type::start]),
	srunning(anim_.sounds()[animation_sound_type::running]),
	send(anim_.sounds()[animation_sound_type::end]),
	animation_type_(animation_type_),
	weapon_type_(weapon_type_),
	start_played_(false)
{
	play(sstart);
}

sanguis::animation_type::type
sanguis::draw::model_part_state::animation_type() const
{
	return animation_type_;
}

sanguis::weapon_type::type
sanguis::draw::model_part_state::weapon_type() const
{
	return weapon_type_;
}

void sanguis::draw::model_part_state::update()
{
	if (!sstart || 
	    (!start_played_ && 
	     sstart->status() == sge::audio::sound_status::stopped))
	{
		start_played_ = true;
		play(srunning,sge::audio::play_mode::loop);
	}
}

sanguis::draw::model_part_state::~model_part_state()
{
	play(send);
}

void sanguis::draw::model_part_state::play(
	sge::audio::sound_ptr const s,
	sge::audio::play_mode::type const ss)
{
	if (s)
		s->play(ss);
}
