#ifndef SANGUIS_CLIENT_MENU_BUTTON_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_BUTTON_HPP_INCLUDED

#include <sge/image/loader_fwd.hpp>
#include <sge/filesystem/path.hpp>
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
		sge::filesystem::path const &,
		sge::string const &);
	
	void process(sge::gui::events::invalid_area const &);
	sge::gui::dim const size_hint() const;
private:
	using sge::gui::widgets::base::process;
};
}
}
}

#endif // SANGUIS_CLIENT_MENU_BUTTON_HPP_INCLUDED
