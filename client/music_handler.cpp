#include "music_handler.hpp"
#include "log.hpp"
#include "../media_path.hpp"
#include "../load/resource/sounds.hpp"
#include <sge/audio/sound/base.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/exception.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/bad_lexical_cast.hpp>

sanguis::client::music_handler::music_handler(
	sge::console::object &_console,
	load::resource::sounds const &_resource)
:
	resource_(_resource),
	volume_connection_(
		_console.insert(
			FCPPT_TEXT("music_volume"),
			std::tr1::bind(
				&music_handler::volume,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			FCPPT_TEXT("Changes the music volume"),
			FCPPT_TEXT("Usage: /music_volume p\np is a value in [0,100] which specifies the volume in percent")
		)
	),
	current_()
{}

void sanguis::client::music_handler::process()
{
	if (!current_)
		return;
	
	if (current_->status() == sge::audio::sound::play_status::stopped)
		next_title();
}

void sanguis::client::music_handler::next_title()
{
	sge::audio::sound::base_ptr const old(
		current_
	);
	
	current_ = load_random();
	
	if(!current_)
		return;
	
	if(old)
		current_->gain(
			old->gain());
	
	current_->play(sge::audio::sound::repeat::once);
}

void sanguis::client::music_handler::volume(sge::console::arg_list const &a,sge::console::object &o)
{
	if (!current_)
	{
		o.emit_error(FCPPT_TEXT("no music files registered, makes no sense to set a volume"));
		return;
	}

	if (a.size() != 2)
	{
		o.emit_error(FCPPT_TEXT("invalid number of arguments"));
		return;
	}

	try
	{
		current_->gain(
			fcppt::lexical_cast<
				sge::audio::scalar
			>(
				a[1]
			)
		);
	}
	catch (fcppt::bad_lexical_cast const &)
	{
		o.emit_error(FCPPT_TEXT("invalid numeric argument"));
	}
}

sge::audio::sound::base_ptr const
sanguis::client::music_handler::load_random() const
{
	// TODO: choose a random one!
	for(
		fcppt::filesystem::directory_iterator it(
			media_path() / FCPPT_TEXT("music")
		);
		it != fcppt::filesystem::directory_iterator();
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
			FCPPT_LOG_WARNING(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("Music file \"")
					<< it->path().string()
					<< FCPPT_TEXT("\" failed to load: \"")
					<< e.string()
					<< FCPPT_TEXT("\"!")
			);
		}
	
	return sge::audio::sound::base_ptr();
}
