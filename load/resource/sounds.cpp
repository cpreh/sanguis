#include "sounds.hpp"
#include "map_get_or_create.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "../../media_path.hpp"
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/buffer.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/bad_sound_alloc.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>

sge::audio::file_ptr const
sanguis::load::resource::sounds::load(
	sound_identifier const &name) const
{
	return map_get_or_create(
		sounds_,
		name, 
		std::tr1::bind(
			&sounds::do_load,
			this,
			std::tr1::placeholders::_1
		)
	);
}

sge::audio::file_ptr const
sanguis::load::resource::sounds::load_uncached(
	fcppt::filesystem::path const &path) const
{
	return ml.load(
		path
	);
}

sanguis::load::resource::sounds::~sounds()
{}

sge::audio::file_ptr const
sanguis::load::resource::sounds::do_load(
	sound_identifier const &name
) const
{
	fcppt::filesystem::path const sound_path(
		media_path() / FCPPT_TEXT("sound") / name
	);

	return ml.load(
		sound_path
	);
}

// FIXME: Put in a separate function
sge::audio::sound::base_ptr const
sanguis::load::resource::sounds::make(
	sge::audio::file_ptr const file,
	sound_type::type const type) const
{
	sge::audio::sound::base_ptr sound;

	try
	{
		switch(type) 
		{
		case sanguis::load::sound_type::stream:
			sound = 
				player->create_nonpositional_stream(
					file);
		break;
		case sanguis::load::sound_type::nonstream:
			{
			sge::audio::buffer_ptr const buf = 
				map_get_or_create(
					buffers_,
					file,
					std::tr1::bind(
						&sge::audio::player::create_buffer,
						player.get(),
						std::tr1::placeholders::_1));
			sound = 
				buf->create_nonpositional();
			}
		break;
		default:
		throw sanguis::exception(
			FCPPT_TEXT("Invalid sound type in load!")
		);
		}

	}
	catch(sge::audio::bad_sound_alloc const &e)
	{
		FCPPT_LOG_WARNING(
			sanguis::load::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Allocation of a sound failed! ")
				<< e.string()
		);
		sound = sge::audio::sound::base_ptr();
	}

	if(sound)
		pool.add(
			sound,
			sge::audio::stop_mode::continue_playing
		);

	return sound;
}

sge::audio::sound::positional_ptr const
sanguis::load::resource::sounds::make_positional(
	sge::audio::file_ptr const file,
	sge::audio::sound::positional_parameters const &params,
	sound_type::type const type) const
{
	sge::audio::sound::positional_ptr sound;

	try
	{
		switch(type) 
		{
		case sanguis::load::sound_type::stream:
			sound = 
				player->create_positional_stream(
					file,
					params);
		break;
		case sanguis::load::sound_type::nonstream:
		{
			sge::audio::buffer_ptr const buf = 
				map_get_or_create(
					buffers_,
					file,
					std::tr1::bind(
						&sge::audio::player::create_buffer,
						player.get(),
						std::tr1::placeholders::_1));
			sound = 
				buf->create_positional(
					params);
		}
		break;
		default:
		throw sanguis::exception(
			FCPPT_TEXT("Invalid sound type in load!")
		);
		}

	}
	catch(sge::audio::bad_sound_alloc const &e)
	{
		FCPPT_LOG_WARNING(
			sanguis::load::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Allocation of a sound failed! ")
				<< e.string()
		);
		sound = sge::audio::sound::positional_ptr();
	}

	if(sound)
		pool.add(
			sound,
			sge::audio::stop_mode::continue_playing
		);

	return sound;
}

sanguis::load::resource::sounds::sounds(
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const player,
	sge::audio::pool &pool
)
:
	ml(ml),
	player(player),
	pool(pool)
{}
