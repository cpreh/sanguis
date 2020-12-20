#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_AND_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_AND_HEALTH_HPP_INCLUDED

#include <sanguis/client/draw2d/radius_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/name_and_health_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/healthbar.hpp>
#include <sanguis/client/draw2d/scene/hover/name.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_decl.hpp>


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

class name_and_health
:
	public sanguis::client::draw2d::scene::hover::base
{
	FCPPT_NONCOPYABLE(
		name_and_health
	);
public:
	name_and_health(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::radius,
		sanguis::client::draw2d::entities::hover::name_and_health const &
	);

	~name_and_health()
	override;
private:
	void
	draw(
		sge::renderer::context::ffp &
	)
	override;

	using
	optional_name
	=
	fcppt::optional::object<
		sanguis::client::draw2d::scene::hover::name
	>;

	using
	healthbar_unique_ptr
	=
	fcppt::unique_ptr<
		sanguis::client::draw2d::scene::hover::healthbar
	>;

	using
	optional_healthbar
	=
	fcppt::optional::object<
		healthbar_unique_ptr
	>;

	optional_healthbar healthbar_;

	optional_name name_;
};

}
}
}
}
}

#endif
