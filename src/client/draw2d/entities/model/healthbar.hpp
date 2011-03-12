#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_HEALTHBAR_HPP_INCLUDED

#include "healthbar_fwd.hpp"
#include "../../sprite/point.hpp"
#include "../../sprite/dim.hpp"
#include "../../sprite/colored/object.hpp"
#include "../../sprite/colored/system.hpp"
#include "../../../health_type.hpp"
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
namespace model
{

class healthbar
{
	FCPPT_NONCOPYABLE(healthbar)
public:
	explicit healthbar(
		sprite::colored::system &
	);

	~healthbar();
	
	void
	update_health(
		health_type health,
		health_type max_health
	);

	health_type
	max_health() const;

	health_type
	health() const;

	void
	attach_to(
		sprite::point const &,
		sprite::dim const &
	);
private:
	void
	pos(
		sprite::point const &
	);

	void
	dim(
		sprite::dim const &
	);

	sprite::point const
	inner_pos() const;

	sprite::dim const
	inner_dim() const;

	health_type	
	remaining_health() const;

	void
	recalc_health();

	sprite::colored::object
		background,
		foreground;
	
	health_type	
		health_,
		max_health_;
};

}
}
}
}
}

#endif
