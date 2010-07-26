#ifndef SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED

#include "../load/resource/sounds_fwd.hpp"
#include <sge/audio/sound_ptr.hpp>
#include <sge/audio/unit.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>

namespace sanguis
{
namespace client
{
class music_handler
{
public:
	music_handler(
		sge::console::object &,
		load::resource::sounds const &);

	void process();
private:
	load::resource::sounds const &resource_;
	fcppt::signal::scoped_connection const volume_connection_;
	sge::audio::sound_ptr current_;

	void next_title();

	void volume(
		sge::console::arg_list const &,
		sge::console::object &);
	
	sge::audio::sound_ptr const
	load_random() const;
};
}
}

#endif
