#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_NAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_HOVER_NAME_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/hover/name_fwd.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace hover
{

class name
{
public:
	name(
		fcppt::string const &,
		sge::image::color::any::object const &
	);

	fcppt::string const &
	text() const;

	sge::image::color::any::object const &
	color() const;
private:
	fcppt::string text_;

	sge::image::color::any::object color_;
};

}
}
}
}
}

#endif
