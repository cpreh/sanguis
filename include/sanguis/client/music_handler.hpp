#ifndef SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED
#define SANGUIS_CLIENT_MUSIC_HANDLER_HPP_INCLUDED

#include <sanguis/client/music_handler_fwd.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/console/arg_list.hpp>
#include <sge/console/object_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{

class music_handler
{
	FCPPT_NONCOPYABLE(
		music_handler
	);
public:
	music_handler(
		sge::console::object &,
		load::resource::sounds const &
	);

	~music_handler();

	void
	process();
private:
	void
	next_title();

	void
	volume(
		sge::console::arg_list const &,
		sge::console::object &
	);

	sge::audio::sound::base_ptr const
	load_random() const;

	load::resource::sounds const &resource_;

	fcppt::signal::scoped_connection const volume_connection_;

	sge::audio::sound::base_ptr current_;

};

}
}

#endif
