#ifndef SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED

#include "sprite.hpp"

namespace sanguis
{
namespace draw
{

class healthbar : public sprite {
public:
	healthbar();
	void health(sge::space_unit);
	void max_health(sge::space_unit);
	sge::space_unit health() const;
	void attach_to(
		const sge::sprite::point&,
		const sge::sprite::dim&);
private:
	void pos(const sge::sprite::point&);
	void dim(const sge::sprite::dim&);
	const sge::sprite::point inner_pos() const;
	const sge::sprite::dim inner_dim() const;
	sge::sprite::object& border();
	const sge::sprite::object& border() const;
	sge::sprite::object& inner();
	const sge::sprite::object& inner() const;
	sge::space_unit remaining_health() const;
	void recalc_health();

	sge::space_unit health_,
	                max_health_;
};

}
}

#endif
