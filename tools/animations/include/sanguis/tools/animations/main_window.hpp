#ifndef SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED

#include <sanguis/model/animation_name_fwd.hpp>
#include <sanguis/model/part_name_fwd.hpp>
#include <sanguis/model/weapon_category_name_fwd.hpp>
#include <sanguis/tools/animations/frame.hpp>
#include <sanguis/tools/animations/frame_container.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <sanguis/tools/animations/optional_animation_ref_fwd.hpp>
#include <sanguis/tools/animations/path_model_pair.hpp>
#include <sanguis/tools/animations/sge_systems_fwd.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <memory>
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
	actionSound();

	void
	selectedPartChanged();

	void
	selectedWeaponChanged();

	void
	selectedAnimationChanged();

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

	void
	open_json(
		boost::filesystem::path const &
	);

	typedef
	fcppt::optional<
		sanguis::model::part_name
	>
	optional_part_name;

	typedef
	fcppt::optional<
		sanguis::model::weapon_category_name
	>
	optional_weapon_category_name;

	typedef
	fcppt::optional<
		sanguis::model::animation_name
	>
	optional_animation_name;

	optional_part_name
	selected_part() const;

	optional_weapon_category_name
	selected_weapon_category() const;

	optional_animation_name
	selected_animation() const;

	typedef
	fcppt::optional<
		boost::filesystem::path
	>
	optional_path;

	optional_path
	resource_path();

	void
	message_box(
		QMessageBox::Icon,
		QString const &,
		QString const &
	);

	sanguis::tools::animations::sge_systems const &sge_systems_;

	std::unique_ptr<
		Ui::MainWindow
	> const ui_;

	typedef
	fcppt::optional<
		sanguis::tools::animations::path_model_pair
	>
	optional_path_model_pair;

	optional_path_model_pair loaded_model_;

	sanguis::tools::animations::image_file_map image_files_;

	sanguis::tools::animations::frame_container frames_;
};

}
}
}

#endif
