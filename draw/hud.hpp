#ifndef SANGUIS_DRAW_HUD_HPP_INCLUDED
#define SANGUIS_DRAW_HUD_HPP_INCLUDED

#include "exp_type.hpp"
#include "level_type.hpp"
#include "../time_type.hpp"
#include <sge/font/object_fwd.hpp>
#include <sge/time/frames_counter.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace draw
{

class hud {
	SGE_NONCOPYABLE(hud)
public:
	explicit hud(
		sge::font::object &);
	void experience(
		exp_type);
	void level(
		level_type);
	void update(
		time_type);
private:
	sge::font::object        &font;
	exp_type                  experience_;
	level_type                level_;
	sge::time::frames_counter frames_counter;
};

}
}

#endif
