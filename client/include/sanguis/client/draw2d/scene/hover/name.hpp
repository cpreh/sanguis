#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
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
:
	public sanguis::client::draw2d::scene::hover::base
{
	FCPPT_NONCOPYABLE(
		name
	);
public:
	name(
		sanguis::client::draw2d::scene::hover::parameters const &,
		sanguis::client::draw2d::entities::hover::name const &
	);

	~name()
	override;
private:
	void
	draw(
		sge::renderer::context::ffp &
	)
	override;

	sge::font::draw::static_text text_;
};

}
}
}
}
}

#endif
