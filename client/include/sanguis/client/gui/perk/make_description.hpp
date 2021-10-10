#ifndef SANGUIS_CLIENT_GUI_PERK_MAKE_DESCRIPTION_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_MAKE_DESCRIPTION_HPP_INCLUDED

#include <sanguis/client/perk/info_fwd.hpp>
#include <sge/font/string.hpp>

namespace sanguis::client::gui::perk
{

sge::font::string make_description(sanguis::client::perk::info const &);

}

#endif
