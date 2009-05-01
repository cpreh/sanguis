#include "sounds.hpp"
#include "map_get_or_create.hpp"
#include "../../exception.hpp"
#include "../../media_path.hpp"
#include <sge/filesystem/path.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>

namespace
{

sge::audio::sound_ptr const
make_sound(
	sge::audio::player_ptr const player,
	sge::audio::file_ptr const file,
	sanguis::load::sound_type::type const type)
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
			SGE_TEXT("Invalid sound type in load!")
		);
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
		boost::bind(
			&sounds::do_load,
			this,
			_1
		)
	);
}

sanguis::load::resource::sounds::~sounds()
{}

sge::audio::file_ptr const
sanguis::load::resource::sounds::do_load(
	sound_identifier const &name) const
{
	sge::filesystem::path const sound_path(
		media_path() / SGE_TEXT("sound") / name
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
