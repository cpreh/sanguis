#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_LIGHT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_LIGHT_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/light_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/client/system_ref.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis::client::draw2d::scene
{

class light
{
	FCPPT_NONMOVABLE(
		light
	);
public:
	light(
		sanguis::client::load::context_cref,
		sanguis::client::draw2d::sprite::client::system_ref,
		sge::viewport::manager_ref
	);

	~light();

	void
	draw(
		sge::renderer::context::core & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)
private:
	void
	reset_viewport();

	sanguis::client::draw2d::sprite::client::system_ref const client_system_;

	sge::texture::part const &texture_;

	sanguis::client::draw2d::sprite::client::object sprite_;

	sge::renderer::state::core::sampler::object_unique_ptr const sampler_state_;

	fcppt::signal::auto_connection const viewport_connection_;
};

}

#endif
