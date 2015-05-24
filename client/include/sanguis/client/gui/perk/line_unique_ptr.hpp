#ifndef SANGUIS_CLIENT_GUI_PERK_LINE_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_LINE_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/client/gui/perk/line_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

typedef
fcppt::unique_ptr<
	sanguis::client::gui::perk::line
>
line_unique_ptr;

}
}
}
}

#endif
