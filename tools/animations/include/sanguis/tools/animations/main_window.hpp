#ifndef SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED

#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/sge_systems_fwd.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QMainWindow>
#include <QString>
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
		sanguis::tools::animations::sge_systems &
	);

	~main_window();
public Q_SLOTS:
	void
	actionJSON();

	void
	actionSave();

	void
	actionQuit();

	void
	selectedPartChanged(
		QString const &
	);

	void
	selectedWeaponChanged(
		QString const &
	);

	void
	selectedAnimationChanged(
		QString const &
	);

	void
	globalDelayChanged(
		int
	);
private:
	sanguis::tools::animations::sge_systems &sge_systems_;

	fcppt::scoped_ptr<
		Ui::MainWindow
	> const ui_;

	typedef
	fcppt::optional<
		sanguis::model::object
	>
	optional_model;

	optional_model loaded_model_;

	QString json_file_;
};

}
}
}

#endif
