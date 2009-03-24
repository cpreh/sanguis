#ifndef SANGUIS_DRAW_BACKGROUND_HPP_INCLUDED
#define SANGUIS_DRAW_BACKGROUND_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "system_fwd.hpp"
#include "entity.hpp"
#include "object.hpp"
#include <sge/renderer/texture_fwd.hpp>

namespace sanguis
{
namespace draw
{
class background : public entity {
public:
	explicit background(
		draw::environment const &);
	
	void paint_dead(
		draw::system &);
private:
	void update(
		time_type);

	sge::renderer::texture_ptr tex;	
	object sprite;
};

}
}

#endif
