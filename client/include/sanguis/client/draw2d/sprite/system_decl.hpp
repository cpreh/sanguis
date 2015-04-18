#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_DECL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/buffers_decl.hpp>
#include <sanguis/client/draw2d/sprite/state.hpp>
#include <sanguis/client/draw2d/sprite/system_fwd.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/sprite/intrusive/ordered/collection_decl.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{

template<
	typename Choices,
	typename Category
>
class system
{
	FCPPT_NONCOPYABLE(
		system
	);

	typedef
	sge::sprite::intrusive::ordered::collection<
		Choices,
		Category
	>
	collection;

	typedef
	typename
	collection::connection_ref
	connection_ref;
public:
	system(
		sge::renderer::device::core &,
		// TODO: Make it possible to omit the states if they do nothing
		sanguis::client::draw2d::sprite::state &
	);

	~system();

	connection_ref const
	connection(
		Category
	);

	void
	render(
		sge::renderer::context::core &,
		Category
	);

	sge::renderer::device::core &
	renderer() const;
private:
	typedef
	sanguis::client::draw2d::sprite::buffers<
		Choices
	>
	sge_buffers;

	sanguis::client::draw2d::sprite::state &state_;

	sge_buffers buffers_;

	collection collection_;
};

}
}
}
}

#endif
