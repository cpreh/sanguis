#ifndef SANGUIS_CLIENT_GUI_PERK_ACTIVATION_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_ACTIVATION_HPP_INCLUDED

#include "chooser_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class activation
{
	FCPPT_NONCOPYABLE(
		activation
	);
public:
	explicit activation(
		perk::chooser &
	);

	~activation();
private:
	perk::chooser &instance_;
};

}
}
}
}

#endif
