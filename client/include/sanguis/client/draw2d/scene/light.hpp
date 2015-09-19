#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_LIGHT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_LIGHT_HPP_INCLUDED

#include <sanguis/client/draw2d/player_center_fwd.hpp>
#include <sanguis/client/draw2d/scene/light_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class light
{
	FCPPT_NONCOPYABLE(
		light
	);
public:
	light(
		sanguis::client::load::context const &,
		sanguis::client::draw2d::sprite::client::system &,
		sge::viewport::manager &
	);

	~light();

	void
	draw(
		sge::renderer::context::core &,
		sanguis::client::draw2d::player_center
	);
private:
	void
	reset_viewport();

	sanguis::client::draw2d::sprite::client::system &client_system_;

	sge::texture::part const &texture_;

	sanguis::client::draw2d::sprite::client::object sprite_;

	sge::renderer::state::core::sampler::object_unique_ptr const sampler_state_;

	fcppt::signal::auto_connection const viewport_connection_;
};

}
}
}
}

#endif
