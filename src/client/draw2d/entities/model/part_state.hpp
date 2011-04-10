#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PART_STATE_HPP_INCLUDED

#include "part_state_fwd.hpp"
#include "../../sprite/point.hpp"
#include "../../../../load/model/part_fwd.hpp"
#include "../../../../load/model/animation_fwd.hpp"
#include "../../../../animation_type.hpp"
#include "../../../../animation_sound_type.hpp"
#include "../../../../weapon_type.hpp"
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <fcppt/container/array_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class part_state
{
	FCPPT_NONCOPYABLE(
		part_state
	);
public:
	part_state(
		load::model::part const &,
		animation_type::type,
		weapon_type::type
	);

	sanguis::animation_type::type
	animation_type() const;

	void
	update(
		draw2d::sprite::point const &
	);

	void
	stop();

	~part_state();
private:
	load::model::animation const &anim_;

	typedef fcppt::container::array<
		sge::audio::sound::positional_ptr,
		sanguis::animation_sound_type::size
	> sound_array;

	sound_array const sounds_;

	sanguis::animation_sound_type::type current_sound_index_;

	animation_type::type const animation_type_;

	void
	play(
		sge::audio::sound::repeat::type
	);
	
	sge::audio::sound::positional_ptr const
	current_sound() const;
};

}
}
}
}
}

#endif
