#include <sanguis/client/draw2d/scene/world/error_texture.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/tiles/error.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::texture::part const &
sanguis::client::draw2d::scene::world::error_texture(
	sanguis::client::load::tiles::context &_context,
	sanguis::tiles::error const _error
)
{
	switch(
		_error
	)
	{
	case sanguis::tiles::error::missing_foreground:
		return
			_context.missing_texture();
	case sanguis::tiles::error::missing_background:
		return
			_context.missing_background_texture();
	case sanguis::tiles::error::missing_object:
		return
			_context.missing_object_texture();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
