#ifndef SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED

#include "optional_delay.hpp"
#include "optional_texture_identifier.hpp"
#include "../resource/textures_fwd.hpp"
#include "../resource/sounds_fwd.hpp"
#include <fcppt/filesystem/path.hpp>
#include <sge/renderer/dim_type.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/optional_impl.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

struct global_parameters {
	global_parameters(
		fcppt::filesystem::path const &,
		resource::textures const &,
		sge::renderer::dim_type const &cell_size,
		optional_delay const &,
		optional_texture_identifier const &,
		resource::sounds const &);
	
	fcppt::filesystem::path const &
	path() const;

	resource::textures const &
	textures() const;

	sge::renderer::dim_type const &
	cell_size() const;

	optional_delay const &
	delay() const;

	optional_texture_identifier const &
	texture() const;

	global_parameters const
	new_texture(
		optional_texture_identifier const &) const;
	
	resource::sounds const &
	sounds() const;
private:
	fcppt::filesystem::path const path_;
	resource::textures const &textures_;
	sge::renderer::dim_type const cell_size_;
	optional_delay const delay_;
	optional_texture_identifier const texture_;
	resource::sounds const &sounds_;
};

}
}
}

#endif
