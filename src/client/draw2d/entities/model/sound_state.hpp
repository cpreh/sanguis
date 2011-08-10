#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_SOUND_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_SOUND_STATE_HPP_INCLUDED

#include "sound_state_fwd.hpp"
#include "../../sprite/point.hpp"
#include "../../../../load/model/animation/sound_fwd.hpp"
#include "../../../../animation_sound_type.hpp"
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

class sound_state
{
	FCPPT_NONCOPYABLE(
		sound_state
	);
public:
	explicit sound_state(
		load::model::animation::sound const &
	);

	void
	update(
		draw2d::sprite::point const &
	);

	void
	stop();

	~sound_state();
private:
	typedef fcppt::container::array<
		sge::audio::sound::positional_ptr,
		sanguis::animation_sound_type::size
	> sound_array;

	sound_array const sounds_;

	sanguis::animation_sound_type::type current_sound_index_;

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
