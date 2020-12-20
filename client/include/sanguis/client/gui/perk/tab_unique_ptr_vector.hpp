#ifndef SANGUIS_CLIENT_GUI_PERK_TAB_UNIQUE_PTR_VECTOR_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_TAB_UNIQUE_PTR_VECTOR_HPP_INCLUDED

#include <sanguis/client/gui/perk/tab_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

using
tab_unique_ptr_vector
=
std::vector<
	sanguis::client::gui::perk::tab_unique_ptr
>;

}
}
}
}

#endif
