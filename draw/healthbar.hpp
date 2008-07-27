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
		system &);
	void health(sge::space_unit);
	void max_health(sge::space_unit);
	sge::space_unit max_health() const;
	sge::space_unit health() const;
	void attach_to(
		sge::sprite::point const &,
		sge::sprite::dim const &);
	bool dead() const;
private:
	void pos(sge::sprite::point const &);
	void dim(sge::sprite::dim const &);
	sge::sprite::point const inner_pos() const;
	sge::sprite::dim const inner_dim() const;
	object &border();
	object const &border() const;
	object &inner();
	object const &inner() const;
	sge::space_unit remaining_health() const;
	void recalc_health();

	sge::space_unit health_,
	                max_health_;
};

}
}

#endif
