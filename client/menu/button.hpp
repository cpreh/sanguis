#ifndef SANGUIS_CLIENT_MENU_BUTTON_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_BUTTON_HPP_INCLUDED

#include <sge/image/loader_fwd.hpp>
#include <fcppt/filesystem/path.hpp>
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/string.hpp>

namespace sanguis
{
namespace client
{
namespace menu
{
class button : public sge::gui::widgets::buttons::image
{
public:
	button(
		sge::gui::widgets::parent_data const &,
		sge::image::loader_ptr,
		fcppt::filesystem::path const &,
		sge::string const &);
	
	void process_invalid_area(
		sge::gui::events::invalid_area const &);
	sge::gui::dim const optimal_size() const;
};
}
}
}

#endif // SANGUIS_CLIENT_MENU_BUTTON_HPP_INCLUDED
