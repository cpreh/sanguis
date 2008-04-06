#ifndef SANGUIS_DRAW_BULLET_HPP_INCLUDED
#define SANGUIS_DRAW_BULLET_HPP_INCLUDED

#include "sprite.hpp"

namespace sanguis
{
namespace draw
{

class bullet : public sprite {
public:
	bullet(
		entity_id id);
private:
	void update(time_type);
	sge::sprite::point origin;
};

}
}

#endif
