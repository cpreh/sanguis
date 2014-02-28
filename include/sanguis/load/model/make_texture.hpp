#ifndef SANGUIS_LOAD_MODEL_MAKE_TEXTURE_HPP_INCLUDED
#define SANGUIS_LOAD_MODEL_MAKE_TEXTURE_HPP_INCLUDED

#include <sanguis/load/model/global_parameters_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>


namespace sanguis
{
namespace load
{
namespace model
{

sge::texture::const_part_shared_ptr
make_texture(
	sanguis::load::model::global_parameters const &
);

}
}
}

#endif
