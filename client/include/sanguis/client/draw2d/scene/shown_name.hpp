#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_SHOWN_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_SHOWN_NAME_HPP_INCLUDED

#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <sanguis/client/draw2d/scene/shown_name_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class shown_name
{
public:
	shown_name(
		sanguis::client::draw2d::center,
		sanguis::client::draw2d::radius,
		sanguis::client::draw2d::entities::name const &
	);

	sanguis::client::draw2d::center const
	center() const;

	sanguis::client::draw2d::radius const
	radius() const;

	sanguis::client::draw2d::entities::name const &
	name() const;
private:
	sanguis::client::draw2d::center center_;

	sanguis::client::draw2d::radius radius_;

	sanguis::client::draw2d::entities::name name_;
};

}
}
}
}

#endif
