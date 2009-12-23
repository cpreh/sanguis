#ifndef SANGUIS_CLIENT_MENU_MOVER_HPP_INCLUDED
#define SANGUIS_CLIENT_MENU_MOVER_HPP_INCLUDED

#include "../../time_type.hpp"
#include <sge/gui/manager_fwd.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <map>

namespace sanguis
{
namespace client
{
namespace menu
{
class mover
{
FCPPT_NONCOPYABLE(mover)
public:
	mover(
		sge::gui::manager &,
		sge::gui::widgets::base &);
	
	void update(
		time_type const &);
	
	void reset(sge::gui::widgets::base &);
	typedef float float_type;
	typedef fcppt::math::vector::static_<float_type,2>::type float_vector;
	typedef fcppt::math::dim::static_<float_type,2>::type float_dim;
private:
	struct entry
	{
		float_vector current;
		float_vector target;
	};

	typedef std::map<
		sge::gui::widgets::base*,
		entry	
	> container;

	sge::gui::manager &man_;
	sge::gui::widgets::base *current_;
	entry current_entry_;
	container to_move_;

	float_type const
		speed_,
		push_distance_,
		threshold_;
	
	float_type remaining_time_;

	void update_position(
		sge::gui::widgets::base&,
		entry &,
		time_type const &);
	void update_visibility(
		sge::gui::widgets::base&,
		entry const &);
	float_vector const random_pos() const;
};
}
}
}

#endif
