#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED

#include "hud_fwd.hpp"
#include "../../exp.hpp"
#include "../../level.hpp"
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/text/drawer_fwd.hpp>
#include <sge/time/frames_counter.hpp>
#include <fcppt/noncopyable.hpp>
#include <ctime>

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
		sge::font::metrics &,
		sge::font::text::drawer &,
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
	draw();
private:
	sge::font::metrics &font_metrics_;
	
	sge::font::text::drawer &font_drawer_;

	client::exp experience_;

	client::level level_;

	std::tm time_;

	sge::time::frames_counter frames_counter_;
};

}
}
}
}

#endif
