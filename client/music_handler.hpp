#ifndef SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED

#include "../load/resource/sounds_fwd.hpp"
#include <sge/audio/sound_fwd.hpp>
#include <sge/audio/unit.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/signal/scoped_connection.hpp>

namespace sanguis
{
namespace client
{
class music_handler
{
public:
	music_handler(
		sge::console::gfx &,
		load::resource::sounds const &);

	void process();
private:
	sge::console::gfx &console_;
	load::resource::sounds const &resource_;
	sge::signal::scoped_connection const volume_connection_;
	sge::audio::sound_ptr current_;

	void next_title();

	void volume(
		sge::console::arg_list const &);
	
	sge::audio::sound_ptr const
	load_random() const;
};
}
}

#endif
