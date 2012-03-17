#ifndef SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_GLOBAL_PARAMETERS_HPP_INCLUDED

#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sanguis/load/model/optional_delay.hpp>
#include <sanguis/load/model/optional_texture_identifier.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace load
{
namespace model
{

class global_parameters
{
	FCPPT_NONASSIGNABLE(
		global_parameters
	);
public:
	global_parameters(
		boost::filesystem::path const &,
		resource::textures const &,
		sge::renderer::dim2 const &cell_size,
		optional_delay const &,
		optional_texture_identifier const &,
		resource::sounds const &
	);

	boost::filesystem::path const &
	path() const;

	resource::textures const &
	textures() const;

	sge::renderer::dim2 const &
	cell_size() const;

	optional_delay const &
	delay() const;

	optional_texture_identifier const &
	texture() const;

	global_parameters const
	new_texture(
		optional_texture_identifier const &
	) const;

	resource::sounds const &
	sounds() const;
private:
	boost::filesystem::path const path_;

	resource::textures const &textures_;

	sge::renderer::dim2 const cell_size_;

	optional_delay const delay_;

	optional_texture_identifier const texture_;

	resource::sounds const &sounds_;
};

}
}
}

#endif
