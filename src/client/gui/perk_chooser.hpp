#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include "perk_chooser_fwd.hpp"
#include "level_type.hpp"
#include "../perk_container.hpp"
#include "../cursor/object_fwd.hpp"
#include "../perk_type.hpp"
#include <sge/font/metrics_ptr.hpp>
#include <sge/gui/widgets/buttons/image.hpp>
#include <sge/gui/widgets/backdrop.hpp>
#include <sge/gui/widgets/label.hpp>
#include <sge/gui/manager.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>

namespace sanguis
{
namespace client
{
namespace gui
{

class perk_chooser
{
	FCPPT_NONCOPYABLE(
		perk_chooser
	);
public:
	typedef fcppt::function::object<
		void (perk_type::type)
	> send_callback;

	perk_chooser(
		sge::renderer::device_ptr,
		sge::input::keyboard::device_ptr,
		sge::input::mouse::device_ptr,
		sge::image2d::multi_loader &,
		sge::font::metrics_ptr,
		send_callback const &,
		sanguis::client::cursor::object_ptr
	);

	void
	process();

	void
	perks(
		perk_container const &
	);

	void
	level_up(
		level_type
	);

	bool
	activated() const;

	void
	activated(
		bool
	);
private:
	// TODO: own header file?
	struct perk_image
	{
		sge::gui::image_ptr 
			normal,
			hover;
	};

	typedef boost::ptr_vector<sge::gui::widgets::buttons::image> button_container;
	typedef std::map<perk_type::type,perk_image> image_map;

	sge::image2d::multi_loader &image_loader_;

	perk_container perks_;
	level_type 
		current_level_,
		consumed_levels_;

	sge::gui::manager manager_;
	sge::gui::widgets::backdrop background_;
	sge::gui::widgets::label perks_left_;
	button_container buttons_;
	fcppt::signal::connection_manager connections_;
	bool dirty_;
	send_callback send_callback_;
	image_map images_;

	level_type levels_left() const;
	void regenerate_label();
	void regenerate_widgets();
	void choose_callback(
		perk_type::type);
	void consume_level();
	image_map::const_iterator const load_from_cache(
		perk_type::type);
};

}
}
}

#endif // SANGUIS_CLIENT_PERK_CHOOSER_HPP_INCLUDED
