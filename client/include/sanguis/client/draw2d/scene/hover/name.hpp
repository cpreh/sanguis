#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/name_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters_fwd.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hover
{

class name
{
	FCPPT_NONCOPYABLE(
		name
	);
public:
	name(
		sanguis::client::draw2d::scene::hover::parameters const &,
		sanguis::client::draw2d::entities::hover::name const &
	);

	name(
		name &&
	);

	name &
	operator=(
		name &&
	);

	~name();

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	sge::font::draw::static_text text_;
};

}
}
}
}
}

#endif
