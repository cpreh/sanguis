#ifndef SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED

#include "sprite.hpp"

namespace sanguis
{
namespace draw
{

class healthbar : public sprite {
public:
	healthbar(
		entity_id id,
		const sge::sprite::point& pos,
		const sge::sprite::dim& dim,
		sge::space_unit health,
		sge::space_unit max_health);
	void health(sge::space_unit);
	void max_health(sge::space_unit);
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
