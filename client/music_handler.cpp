#include "music_handler.hpp"
#include "../media_path.hpp"
#include "../load/resource/sounds.hpp"
#include "../load/sound_collection.hpp"
#include <sge/audio/sound.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>

sanguis::client::music_handler::music_handler(
	load::resource::context const &_resource)
{
	load::sound_container const &s = _resource.sounds().load(
					SGE_TEXT(media_path()/SGE_TEXT("music"))).sounds();
	
	sge::cerr << "loaded " << s.size() << " sounds\n";
	
	if (s.empty())
		return;

	sounds_.reset(
		new load::model::random_sound(
				s,
				_resource,
				load::sound_type::stream));

	next_title();
}

void sanguis::client::music_handler::update()
{
	if (!current_)
		return;
	
	if (current_->status() == sge::audio::sound_status::stopped)
		next_title();
}

void sanguis::client::music_handler::next_title()
{
	current_ = sounds_->random();
	current_->play(sge::audio::play_mode::once);
}
