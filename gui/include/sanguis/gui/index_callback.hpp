#ifndef SANGUIS_GUI_INDEX_CALLBACK_HPP_INCLUDED
#define SANGUIS_GUI_INDEX_CALLBACK_HPP_INCLUDED

#include <sanguis/gui/index_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace gui
{

typedef
std::function<
	sanguis::gui::index_function
>
index_callback;

}
}

#endif
