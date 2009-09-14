#ifndef SANGUIS_DRAW_MODEL_PART_STATE_HPP_INCLUDED
#define SANGUIS_DRAW_MODEL_PART_STATE_HPP_INCLUDED

#include "model_part_fwd.hpp"
#include "../load/model/part_fwd.hpp"
#include "../load/model/animation_fwd.hpp"
#include "../animation_type.hpp"
#include "../weapon_type.hpp"
#include <sge/audio/sound_fwd.hpp>
#include <sge/audio/play_mode.hpp>

namespace sanguis
{
namespace draw
{
class model_part_state
{
	public:
	model_part_state(
		load::model::part const &,
		model_part &,
		animation_type::type,
		weapon_type::type);
	sanguis::animation_type::type animation_type() const;
	sanguis::weapon_type::type weapon_type() const;
	void update();
	~model_part_state();
	private:
	model_part &ref_;
	load::model::animation const &anim_;
	sge::audio::sound_ptr const sstart,srunning,send;
	animation_type::type const animation_type_;
	weapon_type::type const weapon_type_;
	bool start_played_;
	bool loaded_;

	void play(
		sge::audio::sound_ptr,
		sge::audio::play_mode::type = sge::audio::play_mode::once);
	
	void update_sound(sge::audio::sound_ptr);
	void init_sound(sge::audio::sound_ptr);
	void update_sounds();
};
}
}

#endif
