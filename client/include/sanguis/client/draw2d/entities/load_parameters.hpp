#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_LOAD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_LOAD_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_fwd.hpp>
#include <sanguis/client/load/model/collection_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class load_parameters
{
public:
	load_parameters(
		sanguis::diff_clock const &,
		sanguis::random_generator &,
		sanguis::client::sound_manager &,
		sanguis::client::draw2d::sprite::normal::system &,
		sanguis::client::load::model::collection const &
	);

	sanguis::diff_clock const &
	diff_clock() const;

	sanguis::client::sound_manager &
	sound_manager() const;

	sanguis::random_generator &
	random_generator() const;

	sanguis::client::draw2d::sprite::normal::system &
	normal_system() const;

	sanguis::client::load::model::collection const &
	collection() const;
private:
	fcppt::reference<
		sanguis::diff_clock const
	> diff_clock_;

	fcppt::reference<
		sanguis::random_generator
	> random_generator_;

	fcppt::reference<
		sanguis::client::sound_manager
	> sound_manager_;

	fcppt::reference<
		sanguis::client::draw2d::sprite::normal::system
	> normal_system_;

	fcppt::reference<
		sanguis::client::load::model::collection const
	> collection_;
};

}
}
}
}

#endif
