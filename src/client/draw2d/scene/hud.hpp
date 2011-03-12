#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_HPP_INCLUDED

#include "hud_fwd.hpp"
#include "../../exp_type.hpp"
#include "../../level_type.hpp"
#include "../../../time_type.hpp"
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/text/drawer_ptr.hpp>
#include <sge/time/frames_counter.hpp>
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(hud)
public:
	explicit hud(
		sge::font::metrics_ptr,
		sge::font::text::drawer_ptr
	);

	void
	experience(
		exp_type
	);

	void
	level(
		level_type
	);

	void
	update(
		time_type
	);
private:
	sge::font::metrics_ptr const font_metrics_;
	
	sge::font::text::drawer_ptr const font_drawer_;

	exp_type experience_;

	level_type level_;

	sge::time::frames_counter frames_counter;
};

}
}
}
}

#endif
