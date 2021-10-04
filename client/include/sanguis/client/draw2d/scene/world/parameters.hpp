#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/system_ref.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>


namespace sanguis::client::draw2d::scene::world
{

class parameters
{
public:
	parameters(
		sanguis::client::load::context_cref,
		sanguis::client::draw2d::sprite::client::system_ref,
		sge::viewport::manager_ref
	);

	[[nodiscard]]
	sanguis::client::load::context const &
	load_context() const;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::client::system &
	client_system() const;

	[[nodiscard]]
	sge::viewport::manager &
	viewport_manager() const;
private:
	sanguis::client::load::context_cref load_context_;

	sanguis::client::draw2d::sprite::client::system_ref client_system_;

	sge::viewport::manager_ref viewport_manager_;
};

}

#endif
