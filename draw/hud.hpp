#ifndef SANGUIS_DRAW_HUD_HPP_INCLUDED
#define SANGUIS_DRAW_HUD_HPP_INCLUDED

#include "../time_type.hpp"
#include "../messages/types.hpp"
#include <sge/font/fwd.hpp>
#include <boost/noncopyable.hpp>

namespace sanguis
{
namespace draw
{

class hud : boost::noncopyable {
public:
	explicit hud(
		sge::font::font&);
	void experience(
		messages::exp_type);
	void update(
		time_type);
private:
	sge::font::font    &font;
	messages::exp_type experience_;
};

}
}

#endif
