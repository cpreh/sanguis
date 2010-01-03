#ifndef SANGUIS_DRAW_BACKGROUND_HPP_INCLUDED
#define SANGUIS_DRAW_BACKGROUND_HPP_INCLUDED

#include "sprite/normal/system.hpp"
#include "sprite/normal/object.hpp"
#include "environment_fwd.hpp"
#include "entity.hpp"
#include <sge/sprite/object_decl.hpp>
#include <sge/renderer/texture_ptr.hpp>

namespace sanguis
{
namespace draw
{

class background
:
	public entity
{
public:
	explicit background(
		draw::environment const &
	);

	~background();
	
	void
	paint_dead(
		draw::sprite::normal::system &
	);
private:
	void
	update(
		time_type
	);

	sge::renderer::texture_ptr tex;	
	draw::sprite::normal::object sprite;
};

}
}

#endif
