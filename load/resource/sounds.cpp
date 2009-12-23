#include "sounds.hpp"
#include "map_get_or_create.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "../../media_path.hpp"
#include <fcppt/filesystem/path.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/bad_sound_alloc.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <tr1/functional>

namespace
{

sge::audio::sound_ptr const
make_sound(
	sge::audio::player_ptr const player,
	sge::audio::file_ptr const file,
	sanguis::load::sound_type::type const type)
{
	try
	{
		switch(type) {
		case sanguis::load::sound_type::stream:
			return player->create_stream_sound(
				file
			);
		case sanguis::load::sound_type::nonstream:
			return player->create_nonstream_sound(
				file
			);
		default:;
			throw sanguis::exception(
				FCPPT_TEXT("Invalid sound type in load!")
			);
		}
	}
	catch(sge::audio::bad_sound_alloc const &e)
	{
		SGE_LOG_WARNING(
			sanguis::load::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Allocation of a sound failed! ")
				<< e.string()
		);
		return sge::audio::sound_ptr();
	}
}

}

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
	sound_identifier const &name) const
{
	fcppt::filesystem::path const sound_path(
		media_path() / FCPPT_TEXT("sound") / name
	);

	return ml.load(
		sound_path
	);
}

sge::audio::sound_ptr const
sanguis::load::resource::sounds::make(
	sge::audio::file_ptr const file,
	sound_type::type const type) const
{
	sge::audio::sound_ptr const sound_(
		make_sound(
			player,
			file,
			type
		)
	);

	if(sound_)
		pool.add(
			sound_,
			sge::audio::stop_mode::continue_playing
		);

	return sound_;
}

sanguis::load::resource::sounds::sounds(
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const player,
	sge::audio::pool &pool)
:
	ml(ml),
	player(player),
	pool(pool)
{}
