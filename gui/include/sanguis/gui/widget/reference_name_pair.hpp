#ifndef SANGUIS_GUI_WIDGET_REFERENCE_NAME_PAIR_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_REFERENCE_NAME_PAIR_HPP_INCLUDED

#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_name_pair_fwd.hpp>
#include <sge/font/string.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class reference_name_pair
{
public:
	SANGUIS_GUI_SYMBOL
	reference_name_pair(
		sanguis::gui::widget::reference,
		sge::font::string const &
	);

	sanguis::gui::widget::reference const
	reference() const;

	sge::font::string const &
	name() const;
private:
	sanguis::gui::widget::reference reference_;

	sge::font::string name_;
};

}
}
}

#endif
