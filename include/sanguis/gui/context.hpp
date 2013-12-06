#ifndef SANGUIS_GUI_CONTEXT_HPP_INCLUDED
#define SANGUIS_GUI_CONTEXT_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace gui
{

class context
{
public:
	context();

	~context();

	void
	focus(
		sanguis::gui::widget::base &
	);

	void
	destroy(
		sanguis::gui::widget::base &
	);

	sanguis::gui::widget::optional_ref const
	focus() const;
private:
	sanguis::gui::widget::optional_ref focus_;
};

}
}

#endif
