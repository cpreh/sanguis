#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_LEVEL_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_LEVEL_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/level_fwd.hpp>
#include <sge/texture/const_part_ref.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class level
{
public:
	level(
		sanguis::client::draw2d::z_ordering,
		sge::texture::const_part_ref
	);

	sanguis::client::draw2d::z_ordering
	z_ordering() const;

	sge::texture::const_part_ref const
	texture() const;
private:
	sanguis::client::draw2d::z_ordering z_ordering_;

	sge::texture::const_part_ref texture_;
};

}
}
}
}

#endif
