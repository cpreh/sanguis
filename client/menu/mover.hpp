#ifndef SANGUIS_CLIENT_MENU_MOVER_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MOVER_HPP_INCLUDED

#include "../../time_type.hpp"
#include <sge/gui/manager_fwd.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace client
{
namespace menu
{
class mover
{
SGE_NONCOPYABLE(mover)
public:
	mover(
		sge::gui::manager &,
		sge::gui::widget &);
	
	void update(
		time_type const &);
	
	void reset(sge::gui::widget &);
	typedef float float_type;
	typedef sge::math::vector::static_<float_type,2>::type float_vector;
	typedef sge::math::dim::static_<float_type,2>::type float_dim;

private:

	struct entry
	{
		float_vector current;
		float_vector target;
	};

	typedef std::map<
		sge::gui::widget*,
		entry	
	> container;

	sge::gui::manager &man_;
	sge::gui::widget *current_;
	entry current_entry_;
	container to_move_;

	float_type const speed_,
	                 push_distance_,
									 threshold_;

	void update_position(
		sge::gui::widget&,
		entry &,
		time_type const &);
	void update_visibility(
		sge::gui::widget&,
		entry const &);
	float_vector const random_pos() const;
};
}
}
}

#endif
