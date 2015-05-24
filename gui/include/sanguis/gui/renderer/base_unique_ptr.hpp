#ifndef SANGUIS_GUI_RENDERER_BASE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_GUI_RENDERER_BASE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/gui/renderer/base_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace gui
{
namespace renderer
{

typedef
fcppt::unique_ptr<
	sanguis::gui::renderer::base
>
base_unique_ptr;

}
}
}

#endif
