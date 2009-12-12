#ifndef SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "sprite/colored/object.hpp"

namespace sanguis
{
namespace draw
{

class healthbar
{
public:
	explicit healthbar(
		draw::environment const &
	);
	
	void
	update_health(
		funit health,
		funit max_health
	);

	funit max_health() const;
	funit health() const;

	void
	attach_to(
		sprite::point const &,
		sprite::dim const &
	);
private:
	using sprite::health;
	using sprite::max_health;

	void pos(sprite::point const &);
	void dim(sprite::dim const &);
	sprite::point const inner_pos() const;
	sprite::dim const inner_dim() const;
	funit remaining_health() const;
	void recalc_health();

	sprite::colored::object
		background,
		foreground;
	
	funit
		health_,
		max_health_;
};

}
}

#endif
