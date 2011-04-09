#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_HPP_INCLUDED

#include "background_fwd.hpp"
#include "../sprite/client/object.hpp"
#include "../sprite/client/system.hpp"
#include "../vector2.hpp"
#include "../../../load/context_fwd.hpp"
#include <sge/sprite/object_decl.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

class background
{
	FCPPT_NONCOPYABLE(
		background
	);
public:
	background(
		load::context const &,
		sprite::client::system &,
		sge::viewport::manager &
	);

	~background();

	void
	render(
		draw2d::vector2 const &translation
	);
private:
	void
	reset_viewport();

	draw2d::sprite::client::system &client_system_;

	sge::texture::const_part_ptr const texture_;

	draw2d::sprite::client::object sprite_;

	fcppt::signal::scoped_connection const viewport_connection_;
};

}
}
}
}

#endif
