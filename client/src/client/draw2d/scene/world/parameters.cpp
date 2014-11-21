#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/parameters.hpp>
#include <sanguis/client/draw2d/sprite/client/system_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>


sanguis::client::draw2d::scene::world::parameters::parameters(
	sanguis::client::load::context const &_load_context,
	sanguis::client::draw2d::sprite::client::system &_client_system,
	sge::viewport::manager &_viewport_manager
)
:
	load_context_(
		_load_context
	),
	client_system_(
		_client_system
	),
	viewport_manager_(
		_viewport_manager
	)
{
}

sanguis::client::load::context const &
sanguis::client::draw2d::scene::world::parameters::load_context() const
{
	return
		load_context_;
}

sanguis::client::draw2d::sprite::client::system &
sanguis::client::draw2d::scene::world::parameters::client_system() const
{
	return
		client_system_;
}

sge::viewport::manager &
sanguis::client::draw2d::scene::world::parameters::viewport_manager() const
{
	return
		viewport_manager_;
}
