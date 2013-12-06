#ifndef SANGUIS_GUI_TEXT_CALLBACK_HPP_INCLUDED
#define SANGUIS_GUI_TEXT_CALLBACK_HPP_INCLUDED

#include <sanguis/gui/text_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace gui
{

typedef
std::function<
	sanguis::gui::text_function
>
text_callback;

}
}

#endif
