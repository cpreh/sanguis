#include <sanguis/gui/impl/style/simple.hpp>
#include <sanguis/gui/style/base_unique_ptr.hpp>
#include <sanguis/gui/style/create.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sanguis::gui::style::base_unique_ptr
sanguis::gui::style::create()
{
	return
		fcppt::unique_ptr_to_base<
			sanguis::gui::style::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::gui::impl::style::simple
			>()
		);
}
