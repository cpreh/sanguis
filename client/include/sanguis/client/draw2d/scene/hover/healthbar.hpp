#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_HEALTHBAR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HOVER_HEALTHBAR_HPP_INCLUDED

#include <sanguis/client/health_pair_fwd.hpp>
#include <sanguis/client/draw2d/radius_fwd.hpp>
#include <sanguis/client/draw2d/scene/hover/healthbar_fwd.hpp>
#include <sanguis/client/draw2d/sprite/buffers_decl.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/colored/choices.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/sprite/render/range_decl.hpp>
#include <sge/sprite/state/choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
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
	FCPPT_NONCOPYABLE(
		healthbar
	);
public:
	healthbar(
		sge::renderer::device::ffp &,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::radius,
		sanguis::client::health_pair
	);

	~healthbar();

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	typedef
	sanguis::client::draw2d::sprite::buffers<
		sanguis::client::draw2d::sprite::colored::choices
	>
	sge_buffers;

	sge_buffers buffers_;

	typedef
	sge::sprite::render::range<
		sanguis::client::draw2d::sprite::colored::choices
	>
	sprite_range;

	sprite_range range_;

	typedef
	sge::sprite::state::choices<
		brigand::list<>
	>
	state_choices;

	typedef
	sge::sprite::state::object<
		state_choices
	>
	sge_state;

	sge_state state_;
};

}
}
}
}
}

#endif
