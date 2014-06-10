#ifndef SANGUIS_GUI_WIDGET_CHOICES_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_CHOICES_HPP_INCLUDED

#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/index_callback.hpp>
#include <sanguis/gui/index_function.hpp>
#include <sanguis/gui/optional_index.hpp>
#include <sanguis/gui/string_container.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/choices_fwd.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class choices
:
	public sanguis::gui::widget::box_container
{
public:
	SANGUIS_GUI_SYMBOL
	choices(
		sanguis::gui::context &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::gui::string_container const &,
		sanguis::gui::optional_index
	);

	SANGUIS_GUI_SYMBOL
	~choices()
	override;

	SANGUIS_GUI_SYMBOL
	fcppt::signal::auto_connection
	change(
		sanguis::gui::index_callback const &
	);

	SANGUIS_GUI_SYMBOL
	sanguis::gui::optional_index const
	index() const;
private:
	void
	left_clicked();

	void
	right_clicked();

	template<
		typename Func
	>
	void
	update_index(
		Func const &
	);

	sanguis::gui::string_container const strings_;

	sanguis::gui::widget::button left_button_;

	sanguis::gui::widget::text middle_text_;

	sanguis::gui::widget::button right_button_;

	sanguis::gui::optional_index index_;

	fcppt::signal::scoped_connection const left_connection_;

	fcppt::signal::scoped_connection const right_connection_;

	typedef
	fcppt::signal::object<
		sanguis::gui::index_function
	>
	index_signal;

	index_signal index_changed_;
};

}
}
}

#endif
