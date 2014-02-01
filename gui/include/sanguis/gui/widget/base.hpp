#ifndef SANGUIS_GUI_WIDGET_BASE_HPP_INCLUDED
#define SANGUIS_GUI_WIDGET_BASE_HPP_INCLUDED

#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/get_focus_fwd.hpp>
#include <sanguis/gui/symbol.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace widget
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();
public:
	SANGUIS_GUI_SYMBOL
	virtual
	~base() = 0;

	virtual
	void
	on_update(
		sanguis::gui::duration
	);

	virtual
	void
	on_draw(
		sge::renderer::context::ffp &
	) = 0;

	virtual
	sanguis::gui::get_focus const
	on_click(
		sge::rucksack::vector
	);

	virtual
	void
	on_key(
		sge::input::keyboard::key_code
	);

	virtual
	void
	on_char(
		sge::font::char_type
	);

	virtual
	void
	on_focus_changed(
		bool
	);

	virtual
	sge::rucksack::widget::base &
	layout() = 0;

	void
	parent(
		sanguis::gui::widget::optional_ref
	);

	SANGUIS_GUI_SYMBOL
	void
	enable(
		bool
	);

	SANGUIS_GUI_SYMBOL
	bool
	enabled() const;
private:
	virtual
	void
	unregister(
		sanguis::gui::widget::base const &
	);

	sanguis::gui::widget::optional_ref parent_;

	bool enabled_;
};

}
}
}

#endif
