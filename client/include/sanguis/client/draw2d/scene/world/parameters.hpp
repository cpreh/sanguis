#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::client::load::context const &,
		sanguis::client::draw2d::sprite::client::system &,
		sge::viewport::manager &
	);

	sanguis::client::load::context const &
	load_context() const;

	sanguis::client::draw2d::sprite::client::system &
	client_system() const;

	sge::viewport::manager &
	viewport_manager() const;
private:
	sanguis::client::load::context const &load_context_;

	sanguis::client::draw2d::sprite::client::system &client_system_;

	sge::viewport::manager &viewport_manager_;
};

}
}
}
}
}

#endif
