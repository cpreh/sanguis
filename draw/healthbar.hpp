#ifndef SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_DRAW_HEALTHBAR_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "sprite/point.hpp"
#include "sprite/dim.hpp"
#include "sprite/colored/object.hpp"
#include <sge/sprite/object_decl.hpp>
#include <sge/noncopyable.hpp>

namespace sanguis
{
namespace draw
{

class healthbar
{
	SGE_NONCOPYABLE(healthbar)
public:
	explicit healthbar(
		draw::environment const &
	);

	~healthbar();
	
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
