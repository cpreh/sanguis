#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/object_decl.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/texture_animation_decl.hpp>
#include <sanguis/load/model/collection_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class explosion
:
	public sanguis::client::draw2d::entities::own
{
	FCPPT_NONCOPYABLE(
		explosion
	);
public:
	explosion(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::load::model::collection const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::aoe
	);

	~explosion();
private:
	// base overrides

	void
	update()
	override;

	bool
	may_be_removed() const
	override;

	bool ended_;

	typedef sanguis::client::draw2d::sprite::normal::object sprite;

	sprite sprite_;

	sanguis::client::draw2d::sprite::normal::texture_animation animation_;
};

}
}
}
}

#endif
