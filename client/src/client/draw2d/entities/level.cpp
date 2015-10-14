#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/level.hpp>
#include <sge/texture/const_part_ref.hpp>


sanguis::client::draw2d::entities::level::level(
	sanguis::client::draw2d::z_ordering const _z_ordering,
	sge::texture::const_part_ref const _texture
)
:
	z_ordering_{
		_z_ordering
	},
	texture_{
		_texture
	}
{
}

sanguis::client::draw2d::z_ordering
sanguis::client::draw2d::entities::level::z_ordering() const
{
	return
		z_ordering_;
}

sge::texture::const_part_ref
sanguis::client::draw2d::entities::level::texture() const
{
	return
		texture_;
}
