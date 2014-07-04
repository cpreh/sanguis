#ifndef SANGUIS_GUI_MAIN_AREA_BASE_HPP_INCLUDED
#define SANGUIS_GUI_MAIN_AREA_BASE_HPP_INCLUDED

#include <sanguis/gui/main_area/base_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{
namespace main_area
{

class base
{
	FCPPT_NONCOPYABLE(
		base
	);
protected:
	base();

	virtual
	~base() = 0;
public:
	virtual
	sanguis::gui::widget::base &
	widget() = 0;

	virtual
	void
	relayout() = 0;
};

}
}
}

#endif
