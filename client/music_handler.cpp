#include "music_handler.hpp"
#include "../media_path.hpp"
#include "../load/resource/sounds.hpp"
#include "../load/sound_collection.hpp"
#include "../load/resource/sounds.hpp"
#include <sge/audio/sound.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

sanguis::client::music_handler::music_handler(
	sge::console::gfx &_console,
	load::resource::context const &_resource)
:
	console_(_console),
	volume_connection_(
		console_.object().insert(
			SGE_TEXT("music_volume"),
			boost::bind(
				&music_handler::volume,
				this,
				_1
			),
			SGE_TEXT("takes values from 0 to 100, changes the music volume in percent")
		)
	)
{
	load::sound_container const &s(
		_resource.sounds().load(
			media_path() / SGE_TEXT("music")
		).sounds()
	);
	
	if (s.empty())
		return;

	sounds_.reset(
		new load::model::random_sound(
				s,
				_resource,
				load::sound_type::stream));
	
	current_ = sounds_->random();
	current_->play(sge::audio::play_mode::once);
}

void sanguis::client::music_handler::process()
{
	if (!current_)
		return;
	
	if (current_->status() == sge::audio::sound_status::stopped)
		next_title();
}

void sanguis::client::music_handler::next_title()
{
	sge::audio::unit const before = current_->attenuation();
	current_ = sounds_->random();
	current_->play(sge::audio::play_mode::once);
	current_->attenuation(before);
}

void sanguis::client::music_handler::volume(sge::console::arg_list const &a)
{
	if (!current_)
	{
		console_.print(SGE_TEXT("no music files registered, makes no sense to set a volume"));
		return;
	}

	if (a.size() != 2)
	{
		console_.print(SGE_TEXT("invalid number of arguments"));
		return;
	}

	try
	{
		current_->attenuation(boost::lexical_cast<sge::audio::unit>(a[1]));
	}
	catch (boost::bad_lexical_cast const &)
	{
		console_.print(SGE_TEXT("invalid numeric argument"));
	}
}
