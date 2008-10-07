#include "model_part_state.hpp"
#include <sge/audio/sound.hpp>

sanguis::draw::model_part_state::model_part_state(
	load::model::part const &part_,
	animation_type::type const animation_type_,
	weapon_type::type const weapon_type_)
	: anim_(part_[weapon_type_][animation_type_]),
		sstart(anim_.start_sound()),
		srunning(anim_.running_sound()),
		send(anim_.end_sound()),
	  animation_type_(animation_type_),
		weapon_type_(weapon_type_),
		start_played_(false)
{
	play(sstart);
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

void sanguis::draw::model_part_state::play(sge::audio::sound_ptr const s,sge::audio::play_mode::type const ss)
{
	if (s)
		s->play(ss);
}
