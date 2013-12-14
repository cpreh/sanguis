#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_name_pair.hpp>
#include <sge/font/string.hpp>


sanguis::gui::widget::reference_name_pair::reference_name_pair(
	sanguis::gui::widget::reference const _reference,
	sge::font::string const &_name
)
:
	reference_(
		_reference
	),
	name_(
		_name
	)
{
}

sanguis::gui::widget::reference const
sanguis::gui::widget::reference_name_pair::reference() const
{
	return
		reference_;
}

sge::font::string const &
sanguis::gui::widget::reference_name_pair::name() const
{
	return
		name_;
}
