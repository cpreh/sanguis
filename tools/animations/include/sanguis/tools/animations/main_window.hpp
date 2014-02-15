#ifndef SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED

#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QMainWindow>
#include <fcppt/config/external_end.hpp>


namespace Ui
{
	class MainWindow;
}

namespace sanguis
{
namespace tools
{
namespace animations
{

class main_window
:
	public QMainWindow
{
	Q_OBJECT
public:
	explicit
	main_window(
		QWidget *parent = nullptr
	);

	~main_window();
private:
	fcppt::scoped_ptr<
		Ui::MainWindow
	> const ui_;
};

}
}
}

#endif
