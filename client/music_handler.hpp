#ifndef SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED

#include "../load/resource/context.hpp"
#include "../load/model/random_sound.hpp"
#include <sge/audio/sound_fwd.hpp>

namespace sanguis
{
namespace client
{
class music_handler
{
	public:
	music_handler(
		load::resource::context const &);
	void update();
	private:
	load::model::random_sound sounds_;
	sge::audio::sound_ptr current_;
};
}
}

#endif
