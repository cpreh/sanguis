#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/hud_fwd.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/level.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/timer/frames_counter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ctime>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class hud
{
	FCPPT_NONCOPYABLE(
		hud
	);
public:
	hud(
		sge::font::object &,
		sge::renderer::device::ffp &,
		std::tm const &
	);

	void
	experience(
		client::exp
	);

	void
	level(
		client::level
	);

	void
	time(
		std::tm const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	sge::font::object &font_object_;

	sge::renderer::device::ffp &renderer_;

	client::exp experience_;

	client::level level_;

	std::tm time_;

	sge::timer::frames_counter frames_counter_;
};

}
}
}
}

#endif
