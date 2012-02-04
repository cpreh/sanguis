#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_DECL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_SYSTEM_DECL_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/order.hpp>
#include <sanguis/client/draw2d/sprite/system_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/sprite/intrusive/ordered_collection_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
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
	typename Choices
>
class system
{
	FCPPT_NONCOPYABLE(
		system
	);

	typedef sge::sprite::intrusive::ordered_collection<
		Choices,
		sprite::order
	> collection;

	typedef typename collection::connection_type connection_type;
public:
	explicit
	system(
		sge::renderer::device &
	);

	~system();

	connection_type &
	connection(
		sprite::order
	);

	void
	render(
		sprite::order
	);

	sge::renderer::device &
	renderer() const;
private:
	typedef sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			Choices
		>
	> sge_buffers;

	sge_buffers buffers_;

	collection collection_;
};

}
}
}
}

#endif
