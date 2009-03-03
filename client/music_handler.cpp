#include "music_handler.hpp"
#include "../media_path.hpp"
#include "../load/resource/sounds.hpp"
#include "../load/sound_collection.hpp"
#include <sge/audio/sound.hpp>
#include <sge/text.hpp>

sanguis::client::music_handler::music_handler(
	load::resource::context const &_resource)
	: sounds_(
			load::model::random_sound(
				_resource.sounds().load(
					SGE_TEXT(media_path()/SGE_TEXT("music"))).sounds(),
				_resource,
				load::sound_type::stream)),
		current_(sounds_.random())
{
	if (current_)
		current_->play(sge::audio::play_mode::once);
}

void sanguis::client::music_handler::update()
{
	if (!current_)
		return;
	
	if (current_->status() == sge::audio::sound_status::stopped)
	{
		current_ = sounds_.random();
		current_->play(sge::audio::play_mode::once);
	}
}
