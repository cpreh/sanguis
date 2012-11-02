#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_EXPLOSION_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
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
		sanguis::load::model::collection const &,
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::aoe
	);

	~explosion();
private:
	// base overrides

	void
	update();

	bool
	may_be_removed() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::load::model::collection const &model_collection_;

	sanguis::client::draw2d::aoe const aoe_;

	bool ended_;
};

}
}
}
}

#endif
