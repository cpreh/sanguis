#ifndef SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED

#include "../load/resource/context.hpp"
#include "../load/model/random_sound.hpp"
#include <sge/audio/sound_fwd.hpp>
#include <sge/audio/unit.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/scoped_ptr.hpp>

namespace sanguis
{
namespace client
{
class music_handler
{
	public:
	music_handler(
		sge::console::gfx &,
		load::resource::context const &);
	void update();
	private:
	sge::console::gfx &console_;
	sge::signal::auto_connection volume_connection_;
	sge::scoped_ptr<load::model::random_sound> sounds_;
	sge::audio::sound_ptr current_;

	void next_title();
	void volume(sge::console::arg_list const &);
};
}
}

#endif
