#include <sanguis/client/music_handler.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/load/resource/sounds.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/console/callback/parameters.hpp>
#include <sge/font/text/lit.hpp>
#include <sge/exception.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/text.hpp>

sanguis::client::music_handler::music_handler(
	sge::console::object &_console,
	load::resource::sounds const &_resource)
:
	resource_(_resource),
	volume_connection_(
		_console.insert(
			sge::console::callback::parameters(
				std::tr1::bind(
					&music_handler::volume,
					this,
					std::tr1::placeholders::_1,
					std::tr1::placeholders::_2
				),
				sge::console::callback::name(
					SGE_FONT_TEXT_LIT("music_volume")
				)
			)
			.short_description(
				SGE_FONT_TEXT_LIT("Changes the music volume")
			)
			.long_description(
				SGE_FONT_TEXT_LIT("Usage: /music_volume p\np is a value in [0,100] which specifies the volume in percent")
			)
		)
	),
	current_(),
	gain_()
{
}

sanguis::client::music_handler::~music_handler()
{
}

void
sanguis::client::music_handler::process()
{
	if(
		!current_
	)
		return;

	if(
		current_->status() == sge::audio::sound::play_status::stopped
	)
		this->next_title();
}

void
sanguis::client::music_handler::next_title()
{
	current_ = this->load_random();

	if(
		!current_
	)
		return;

	if(
		gain_
	)
		current_->gain(
			*gain_
		);

	current_->play(
		sge::audio::sound::repeat::once
	);
}

void
sanguis::client::music_handler::volume(
	sge::console::arg_list const &_args,
	sge::console::object &_object
)
{
	if(
		!current_
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("no music files registered, makes no sense to set a volume")
		);

		return;
	}

	if(
		_args.size() != 2
	)
	{
		_object.emit_error(
			SGE_FONT_TEXT_LIT("invalid number of arguments")
		);
		return;
	}

	gain_ =
		fcppt::extract_from_string<
			sge::audio::scalar
		>(
			_args[1]
		);

	if(
		!gain_
	)
		_object.emit_error(
			SGE_FONT_TEXT_LIT("invalid numeric argument")
		);
	else
		current_->gain(
			*gain_
		);
}

sge::audio::sound::base_ptr const
sanguis::client::music_handler::load_random() const
{
	// TODO: choose a random one!
	for(
		fcppt::filesystem::directory_iterator it(
			sanguis::media_path()
			/ FCPPT_TEXT("music")
		);
		it != fcppt::filesystem::directory_iterator();
		++it
	)
		try
		{
			return
				resource_.make(
					resource_.load_uncached(
						*it
					),
					load::sound_type::stream
				);
		}
		catch(
			sge::exception const &_error
		)
		{
			FCPPT_LOG_WARNING(
				client::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Music file \"")
					<< fcppt::filesystem::path_to_string(
						it->path()
					)
					<< FCPPT_TEXT("\" failed to load: \"")
					<< _error.string()
					<< FCPPT_TEXT("\"!")
			);
		}

	return sge::audio::sound::base_ptr();
}
