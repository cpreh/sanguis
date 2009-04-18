#include "button.hpp"
#include <sge/gui/make_image.hpp>
#include <sge/gui/manager.hpp>
#include <sge/image/loader.hpp>
#include <sge/text.hpp>

sanguis::client::menu::button::button(
	sge::gui::widgets::parent_data const &parent,
	sge::image::loader_ptr const il,
	sge::filesystem::path const &base,
	sge::string const &name)
	: image(
			parent,
			sge::gui::widgets::parameters(),
			sge::gui::make_image(
				il->load(
					base/name/SGE_TEXT("normal.png"))),
			sge::gui::make_image(
				il->load(
					base/name/SGE_TEXT("hover.png"))),
			sge::gui::make_image(
				il->load(
					base/name/SGE_TEXT("keyboard.png"))),
			sge::gui::make_image(
				il->load(
					base/name/SGE_TEXT("hover_keyboard.png"))))
{
}

void sanguis::client::menu::button::process(
	sge::gui::events::invalid_area const &e)
{
	parent_manager().skin().draw(
		*this,
		e);
}

sge::gui::dim const sanguis::client::menu::button::optimal_size() const
{
	return parent_manager().skin().optimal_size(
		*this);
}
