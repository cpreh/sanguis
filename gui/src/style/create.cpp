#include <sanguis/gui/aux_/style/simple.hpp>
#include <sanguis/gui/style/base_unique_ptr.hpp>
#include <sanguis/gui/style/create.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::gui::style::base_unique_ptr
sanguis::gui::style::create()
{
	return
		fcppt::make_unique_ptr<
			sanguis::gui::aux_::style::simple
		>();
}
