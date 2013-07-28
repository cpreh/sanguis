#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_HEALTHBAR_HPP_INCLUDED

#include <sanguis/client/health.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/client/draw2d/entities/model/healthbar_fwd.hpp>
#include <sanguis/client/draw2d/sprite/dim.hpp>
#include <sanguis/client/draw2d/sprite/point.hpp>
#include <sanguis/client/draw2d/sprite/colored/object.hpp>
#include <sanguis/client/draw2d/sprite/colored/system.hpp>
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
	explicit
	healthbar(
		sanguis::client::draw2d::sprite::colored::system &
	);

	~healthbar();

	void
	update_health(
		sanguis::client::health,
		sanguis::client::max_health
	);

	sanguis::client::max_health const
	max_health() const;

	sanguis::client::health const
	health() const;

	void
	attach_to(
		sanguis::client::draw2d::sprite::point const &,
		sanguis::client::draw2d::sprite::dim const &
	);
private:
	void
	pos(
		sanguis::client::draw2d::sprite::point const &
	);

	void
	dim(
		sanguis::client::draw2d::sprite::dim const &
	);

	sanguis::client::draw2d::sprite::point const
	inner_pos() const;

	sanguis::client::draw2d::sprite::dim const
	inner_dim() const;

	sanguis::client::health const
	remaining_health() const;

	void
	recalc_health();

	sanguis::client::draw2d::sprite::colored::object
		background_,
		foreground_;

	sanguis::client::health health_;

	sanguis::client::max_health max_health_;
};

}
}
}
}
}

#endif
