#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_HEALTHBAR_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/model/healthbar_fwd.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/colored/object.hpp>
#include <sanguis/client/draw2d/sprite/colored/system.hpp>
#include <sanguis/client/health.hpp>
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
	FCPPT_NONCOPYABLE(
		healthbar
	);
public:
	explicit healthbar(
		sprite::colored::system &
	);

	~healthbar();

	void
	update_health(
		client::health health,
		client::health max_health
	);

	client::health const
	max_health() const;

	client::health const
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

	client::health const
	remaining_health() const;

	void
	recalc_health();

	sprite::colored::object
		background_,
		foreground_;

	client::health
		health_,
		max_health_;
};

}
}
}
}
}

#endif
