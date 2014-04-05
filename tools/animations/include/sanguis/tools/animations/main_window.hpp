#ifndef SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED

#include <sanguis/model/object.hpp>
#include <sanguis/tools/animations/frame.hpp>
#include <sanguis/tools/animations/frame_container.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <sanguis/tools/animations/optional_animation_ref_fwd.hpp>
#include <sanguis/tools/animations/sge_systems_fwd.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QMainWindow>
#include <QString>
#include <vector>
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
		sanguis::tools::animations::sge_systems const &
	);

	~main_window();
public Q_SLOTS:
	void
	actionJSON();

	void
	actionResourcePath();

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

	void
	delayChanged(
		int
	);

	void
	soundChanged(
		QString const &
	);
private:
	sanguis::tools::animations::optional_animation_ref const
	current_animation();

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

	sanguis::tools::animations::image_file_map image_files_;

	sanguis::tools::animations::frame_container frames_;
};

}
}
}

#endif
