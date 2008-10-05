#ifndef SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_ANIMATION_HPP_INCLUDED

#include <sge/path.hpp>
#include <sge/sprite/animation_series.hpp>
#include <sge/audio/sound_fwd.hpp>
#include <boost/shared_ptr.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class animation {
public:
	sge::sprite::animation_series const& get() const;
	sge::audio::sound_ptr const start_sound() const;
	sge::audio::sound_ptr const running_sound() const;
	sge::audio::sound_ptr const end_sound() const;
private:
	explicit animation(sge::path const&);

	friend class weapon_category;

	sge::path path;
	mutable boost::shared_ptr<
		sge::sprite::animation_series> anim;
};

}
}
}

#endif
