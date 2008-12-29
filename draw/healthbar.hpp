#ifndef SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED

#include "sprite.hpp"

namespace sanguis
{
namespace draw
{

class healthbar : public sprite {
public:
	explicit healthbar(
		draw::system &);
	void health(funit);
	void max_health(funit);
	funit max_health() const;
	funit health() const;
	void attach_to(
		sge::sprite::point const &,
		sge::sprite::dim const &);
private:
	void pos(sge::sprite::point const &);
	void dim(sge::sprite::dim const &);
	sge::sprite::point const inner_pos() const;
	sge::sprite::dim const inner_dim() const;
	object &border();
	object const &border() const;
	object &inner();
	object const &inner() const;
	funit remaining_health() const;
	void recalc_health();

	funit
		health_,
		max_health_;
};

}
}

#endif
