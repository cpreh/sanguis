#ifndef SANGUIS_DRAW_PARTICLE_PROPERTIES_HPP_INCLUDED
#define SANGUIS_DRAW_PARTICLE_PROPERTIES_HPP_INCLUDED

#include "movement_type.hpp"
#include "align_type.hpp"
#include "../funit.hpp"
#include "../unit.hpp"
#include <sge/minmax_pair_decl.hpp>

namespace sanguis
{
namespace draw
{
namespace particle
{

struct properties {
	typedef sge::minmax_pair<
		unit
	> dispersion_range;

	typedef sge::minmax_pair<
		funit
	> speed_range;

	typedef sge::minmax_pair<
		funit
	> rot_speed_range;

	typedef sge::minmax_pair<
		funit
	> fade_range;

	properties(
		funit anim_speed,
		unsigned spawn_initial,
		funit gen_life_time,
		funit gen_frequency,
		align_type::type align,
		dispersion_range const &,
		speed_range const &,
		rot_speed_range const &,
		bool fade,
		fade_range const &,
		movement_type::type);

	funit anim_speed() const;
	unsigned spawn_initial() const;
	funit gen_life_time() const;
	funit gen_frequency() const;
	align_type::type align() const;
	dispersion_range const &dispersion() const;
	speed_range const &speed() const;
	rot_speed_range const &rot_speed() const;
	bool do_fade() const;
	fade_range const &fade() const;
	movement_type::type movement() const;
private:
	funit anim_speed_;
	unsigned spawn_initial_;
	funit gen_life_time_;
	funit gen_frequency_;
	align_type::type align_;
	dispersion_range dispersion_;
	speed_range speed_;
	rot_speed_range rot_speed_;
	bool do_fade_;
	fade_range fade_;
	movement_type::type movement_;
};

}
}
}

#endif
