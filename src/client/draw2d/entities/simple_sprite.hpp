#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_SIMPLE_SPRITE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_SIMPLE_SPRITE_HPP_INCLUDED

#include "base.hpp"
#include "with_visibility.hpp"
#include "../sprite/client/repetition_type.hpp"
#include "../sprite/client/object.hpp"
#include "../sprite/client/system.hpp"
#include "../sprite/order.hpp"
#include <sge/texture/part_ptr.hpp>
#include <sge/sprite/object_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class simple_sprite
:
	public base,
	public with_visibility
{
	FCPPT_NONCOPYABLE(
		simple_sprite
	);
public:
	simple_sprite(
		sprite::client::system &system_,		
		sprite::order,
		sge::texture::const_part_ptr,
		sprite::client::repetition_type
	);

	~simple_sprite();

	typedef sprite::client::object object_type;

	object_type const &
	object() const;
private:
	// entity overrides
	
	void
	update(
		time_type
	);

	void
	pos(
		sprite::point const &
	);

	void
	dim(
		sprite::dim const &
	);

	sprite::point const
	center() const;

	// with_visibility overrides
	
	void
	visible(
		bool
	);

	object_type sprite_;
};

}
}
}
}

#endif
