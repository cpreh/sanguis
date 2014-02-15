#include <sanguis/tools/animations/main_window.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QMainWindow>
#include <ui_main_window.h>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::main_window::main_window(
	QWidget *const _parent
)
:
	QMainWindow(
		_parent
	),
	ui_(
		fcppt::make_unique_ptr<
			Ui::MainWindow
		>()
	)
{
	ui_->setupUi(
		this
	);
}

sanguis::tools::animations::main_window::~main_window()
{
}
