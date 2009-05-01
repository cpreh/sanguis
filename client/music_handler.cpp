#include "music_handler.hpp"
#include "log.hpp"
#include "../media_path.hpp"
#include "../load/resource/sounds.hpp"
#include <sge/audio/sound.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/log/headers.hpp>
#include <sge/exception.hpp>
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

sanguis::client::music_handler::music_handler(
	sge::console::gfx &_console,
	load::resource::sounds const &_resource)
:
	console_(_console),
	resource_(_resource),
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
	),
	current_()
{}

void sanguis::client::music_handler::process()
{
	if (!current_)
		return;
	
	if (current_->status() == sge::audio::sound_status::stopped)
		next_title();
}

void sanguis::client::music_handler::next_title()
{
	sge::audio::sound_ptr const old(
		current_
	);
	
	current_ = load_random();
	
	if(!current_)
		return;
	
	if(old)
		current_->attenuation(
			old->attenuation()
		);
	
	current_->play(sge::audio::play_mode::once);
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
		current_->attenuation(
			boost::lexical_cast<
				sge::audio::unit
			>(
				a[1]
			)
		);
	}
	catch (boost::bad_lexical_cast const &)
	{
		console_.print(SGE_TEXT("invalid numeric argument"));
	}
}

sge::audio::sound_ptr const
sanguis::client::music_handler::load_random() const
{
	// TODO: choose a random one!
	for(
		sge::filesystem::directory_iterator it(
			media_path() / SGE_TEXT("music")
		);
		it != sge::filesystem::directory_iterator();
		++it
	)
		try
		{
			return resource_.make(
				resource_.load_uncached(
					*it
				),
				load::sound_type::stream
			);
		}
		catch(sge::exception const &e)
		{
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< SGE_TEXT("Music file \"")
					<< it->path().string()
					<< SGE_TEXT("\" failed to load: \"")
					<< e.what()
					<< SGE_TEXT("\"!")
			);
		}
	
	return sge::audio::sound_ptr();
}
