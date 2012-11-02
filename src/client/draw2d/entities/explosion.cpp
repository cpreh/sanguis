#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/draw2d/aoe.hpp>
#include <sanguis/client/draw2d/entities/explosion.hpp>
#include <sanguis/client/draw2d/entities/own.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/load/model/collection_fwd.hpp>


sanguis::client::draw2d::entities::explosion::explosion(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::load::model::collection const &_model_collection,
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::draw2d::aoe const _aoe
)
:
	sanguis::client::draw2d::entities::own(),
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	model_collection_(
		_model_collection
	),
	aoe_(
		_aoe
	),
	ended_(
		false
	)
{
}

sanguis::client::draw2d::entities::explosion::~explosion()
{
}

void
sanguis::client::draw2d::entities::explosion::update()
{
	// TODO: Do something here!
	ended_ = true;
}

bool
sanguis::client::draw2d::entities::explosion::may_be_removed() const
{
	return ended_;
}
