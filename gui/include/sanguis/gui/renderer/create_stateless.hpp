#ifndef SANGUIS_GUI_RENDERER_CREATE_STATELESS_HPP_INCLUDED
#define SANGUIS_GUI_RENDERER_CREATE_STATELESS_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/renderer/base_unique_ptr.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>


namespace sanguis
{
namespace gui
{
namespace renderer
{

SANGUIS_GUI_SYMBOL
sanguis::gui::renderer::base_unique_ptr
create_stateless(
	sge::renderer::device::ffp &
);

}
}
}

#endif
