#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_fwd.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/range.hpp>
#include <sanguis/client/draw2d/scene/world/sprite/state_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis::client::draw2d::scene::world
{

class batch
{
	FCPPT_NONCOPYABLE(
		batch
	);
public:
	explicit
	batch(
		sanguis::client::draw2d::scene::world::sprite::range &&
	);

	batch(
		batch &&
	)
	noexcept;

	batch &
	operator=(
		batch &&
	)
	noexcept;

	~batch();

	void
	draw(
		sge::renderer::context::core &, // NOLINT(google-runtime-references)
		sge::renderer::vertex::declaration const &,
		sanguis::client::draw2d::scene::world::sprite::state & // NOLINT(google-runtime-references)
	) const; // NOLINT(google-runtime-references)
private:
	sanguis::client::draw2d::scene::world::sprite::range range_;
};

}

#endif
