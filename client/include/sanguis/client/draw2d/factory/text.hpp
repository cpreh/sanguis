#ifndef SANGUIS_CLIENT_DRAW2D_FACTORY_TEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_FACTORY_TEXT_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/client/draw2d/entities/own_unique_ptr.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace factory
{

sanguis::client::draw2d::entities::own_unique_ptr
text(
	sanguis::diff_clock_cref,
	sanguis::client::draw2d::sprite::normal::system_ref,
	sge::font::object &, // NOLINT(google-runtime-references)
	sge::font::string const &,
	sanguis::client::draw2d::sprite::center const &,
	sanguis::client::draw2d::sprite::normal::color
);

}
}
}
}

#endif
