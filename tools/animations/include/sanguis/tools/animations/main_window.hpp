#ifndef SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_MAIN_WINDOW_HPP_INCLUDED

#include <sanguis/model/animation_name_fwd.hpp>
#include <sanguis/model/optional_animation_delay_fwd.hpp>
#include <sanguis/model/part_name_fwd.hpp>
#include <sanguis/model/weapon_category_name_fwd.hpp>
#include <sanguis/tools/animations/frame.hpp>
#include <sanguis/tools/animations/frame_container.hpp>
#include <sanguis/tools/animations/image_file_map.hpp>
#include <sanguis/tools/animations/optional_animation_ref_fwd.hpp>
#include <sanguis/tools/animations/path_model_pair.hpp>
#include <sanguis/tools/animations/sge_systems_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/clang_version_at_least.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QTimer>
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

FCPPT_PP_PUSH_WARNING
#if FCPPT_CONFIG_CLANG_VERSION_AT_LEAST(3, 6)
FCPPT_PP_DISABLE_GCC_WARNING(-Winconsistent-missing-override)
#endif
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wsuggest-override)
#endif

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

	~main_window()
	override;
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

	void
	updateFrame();

	void
	playFrames();

	void
	resetFrames();
private:
	sanguis::tools::animations::optional_animation_ref
	current_animation();

	void
	open_json(
		std::filesystem::path const &
	);

	typedef
	fcppt::optional::object<
		sanguis::model::part_name
	>
	optional_part_name;

	typedef
	fcppt::optional::object<
		sanguis::model::weapon_category_name
	>
	optional_weapon_category_name;

	typedef
	fcppt::optional::object<
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
	fcppt::optional::object<
		std::filesystem::path
	>
	optional_path;

	optional_path
	resource_path();

	void
	update_frame_timer();

	sanguis::model::optional_animation_delay
	current_animation_delay();

	void
	message_box(
		QMessageBox::Icon,
		QString const &,
		QString const &
	);

	sanguis::tools::animations::sge_systems const &sge_systems_;

	fcppt::unique_ptr<
		Ui::MainWindow
	> const ui_;

	typedef
	fcppt::optional::object<
		sanguis::tools::animations::path_model_pair
	>
	optional_path_model_pair;

	optional_path_model_pair loaded_model_;

	sanguis::tools::animations::image_file_map image_files_;

	QTimer frame_timer_;

	sanguis::tools::animations::frame_container frames_;

	sanguis::tools::animations::frame_container::const_iterator frame_iterator_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
