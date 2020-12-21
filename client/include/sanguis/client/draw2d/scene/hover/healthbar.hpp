#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_HEALTHBAR_HPP_INCLUDED

#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/radius_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/healthbar_fwd.hpp>
#include <sanguis/client/draw2d/sprite/buffers_decl.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/colored/choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/sprite/render/range_decl.hpp>
#include <sge/sprite/state/choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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

class healthbar
{
	FCPPT_NONMOVABLE(
		healthbar
	);
public:
	healthbar(
		sge::renderer::device::core_ref,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::radius,
		sanguis::client::health_pair
	);

	~healthbar();

	void
	draw(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)
private:
	using
	sge_buffers
	=
	sanguis::client::draw2d::sprite::buffers<
		sanguis::client::draw2d::sprite::colored::choices
	>;

	sge_buffers buffers_;

	using
	sprite_range
	=
	sge::sprite::render::range<
		sanguis::client::draw2d::sprite::colored::choices
	>;

	sprite_range range_;

	using
	state_choices
	=
	sge::sprite::state::choices<
		metal::list<>
	>;

	using
	sge_state
	=
	sge::sprite::state::object<
		state_choices
	>;

	sge_state state_;
};

}
}
}
}
}

#endif
