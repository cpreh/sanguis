#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_LOAD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_LOAD_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/colored/system_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/load/model/collection_fwd.hpp>
#include <fcppt/nonassignable.hpp>


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

class load_parameters
{
	FCPPT_NONASSIGNABLE(
		load_parameters
	);
public:
	load_parameters(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::client::sound_manager &,
		sanguis::client::draw2d::sprite::colored::system &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::load::model::collection const &
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::client::sound_manager &
	sound_manager() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::client::draw2d::sprite::colored::system &
	colored_system() const;

	sanguis::client::draw2d::sprite::normal::system &
	normal_system() const;

	sanguis::load::model::collection const &
	collection() const;
private:
	sanguis::diff_clock const &diff_clock_;

	sanguis::random_generator &random_generator_;

	sanguis::client::sound_manager &sound_manager_;

	sanguis::client::draw2d::sprite::colored::system &colored_system_;

	sanguis::client::draw2d::sprite::normal::system &normal_system_;

	sanguis::load::model::collection const &collection_;
};

}
}
}
}
}

#endif
