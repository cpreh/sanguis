#ifndef SANGUIS_DRAW_EXPLOSION_HPP_INCLUDED
#define SANGUIS_DRAW_EXPLOSION_HPP_INCLUDED

#include "entity.hpp"
#include <sge/sprite/point.hpp>

namespace sanguis
{
namespace draw
{

class environment;

class explosion : public entity {
public:
	explosion(
		draw::environment const &,
		sge::sprite::point const &pos);
private:
	bool may_be_removed() const;
};

}
}

#endif
