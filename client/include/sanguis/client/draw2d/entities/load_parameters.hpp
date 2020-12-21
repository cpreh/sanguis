#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_LOAD_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_LOAD_PARAMETERS_HPP_INCLUDED

#include <sanguis/diff_clock_cref.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/client/sound_manager_fwd.hpp>
#include <sanguis/client/sound_manager_ref.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/normal/system_ref.hpp>
#include <sanguis/client/load/model/collection_cref.hpp>


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
		sanguis::diff_clock_cref,
		sanguis::random_generator_ref,
		sanguis::client::sound_manager_ref,
		sanguis::client::draw2d::sprite::normal::system_ref,
		sanguis::client::load::model::collection_cref
	);

	[[nodiscard]]
	sanguis::diff_clock const &
	diff_clock() const;

	[[nodiscard]]
	sanguis::client::sound_manager &
	sound_manager() const;

	[[nodiscard]]
	sanguis::random_generator &
	random_generator() const;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::normal::system &
	normal_system() const;

	[[nodiscard]]
	sanguis::client::load::model::collection const &
	collection() const;
private:
	sanguis::diff_clock_cref diff_clock_;

	sanguis::random_generator_ref random_generator_;

	sanguis::client::sound_manager_ref sound_manager_;

	sanguis::client::draw2d::sprite::normal::system_ref normal_system_;

	sanguis::client::load::model::collection_cref collection_;
};

}
}
}
}

#endif
