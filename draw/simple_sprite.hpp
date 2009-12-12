#ifndef SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "sprite/client/repetition_type.hpp"
#include "sprite/client/object.hpp"
#include "sprite/order.hpp"
#include "entity.hpp"
#include <sge/texture/part_fwd.hpp>
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/object_decl.hpp>

namespace sanguis
{
namespace draw
{

class simple_sprite : public entity {
public:
	simple_sprite(
		draw::environment const &,
		entity_id,
		sprite::order,
		sge::texture::const_part_ptr,
		sprite::client::repetition_type
	);

	~simple_sprite();
private:
	void update(time_type);
	void pos(sprite::point const &);
	void dim(sprite::dim const &);
	void visible(bool);

	sprite::client::object sprite_;
};

}
}

#endif
