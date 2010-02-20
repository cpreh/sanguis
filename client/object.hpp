#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include "../main_object.hpp"

namespace sanguis
{
namespace client
{

class object
:
	public main_object
{
	FCPPT_NONCOPYABLE(object)
public:
	explicit object(
		sge::systems::instance &
	);

	~object();
private:
	int
	run();

	sge::input::key_state_tracker key_states_;
	
	sge::font::metrics_ptr const font_metrics_;

	sge::font::drawer_ptr const font_drawer_;

	sge::font::object const font_;

	sge::texture::manager texture_manager_;

	sge::console::object console_;

	sge::console::gfx console_gfx_;

	sge::audio::multi_loader audio_loader_;

	sge::audio::pool sound_pool_;

	client::machine machine_;
};

}
}

#endif
