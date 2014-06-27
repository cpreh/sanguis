#ifndef SANGUIS_GUI_MAIN_AREA_HPP_INCLUDED
#define SANGUIS_GUI_MAIN_AREA_HPP_INCLUDED

#include <sanguis/gui/main_area_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace gui
{

class main_area
{
	FCPPT_NONCOPYABLE(
		main_area
	);
protected:
	main_area();

	virtual
	~main_area() = 0;
public:
	virtual
	sanguis::gui::widget::base &
	widget() = 0;
};

}
}

#endif
