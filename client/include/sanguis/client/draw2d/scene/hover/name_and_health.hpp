#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_AND_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_NAME_AND_HEALTH_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/name_and_health_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/healthbar.hpp>
#include <sanguis/client/draw2d/scene/hover/name.hpp>
#include <sanguis/client/draw2d/scene/hover/parameters_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


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
		sanguis::client::draw2d::scene::hover::parameters const &,
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

	typedef
	fcppt::optional<
		sanguis::client::draw2d::scene::hover::name
	>
	optional_name;

	typedef
	std::unique_ptr<
		sanguis::client::draw2d::scene::hover::healthbar
	>
	healthbar_unique_ptr;

	typedef
	fcppt::optional<
		healthbar_unique_ptr
	>
	optional_healthbar;

	optional_healthbar healthbar_;

	optional_name name_;
};

}
}
}
}
}

#endif
