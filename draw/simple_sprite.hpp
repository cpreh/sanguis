#ifndef SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_DRAW_SIMPLE_SPRITE_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "entity.hpp"
#include "object.hpp"
#include <sge/texture/part_fwd.hpp>
#include <sge/sprite/intrusive/order.hpp>

namespace sanguis
{
namespace draw
{
class simple_sprite : public entity {
public:
	simple_sprite(
		draw::environment const &,
		entity_id,
		sge::sprite::intrusive::order,
		sge::texture::const_part_ptr,
		sge::sprite::repetition_type);
private:
	void update(time_type);
	void orientation(sge::sprite::rotation_type);
	void pos(sge::sprite::point const &);
	void dim(sge::sprite::dim const &);
	void visible(bool);
	sge::sprite::rotation_type orientation() const;
	object &get();
	object const &get() const;

	object sprite_;
};

}
}

#endif
