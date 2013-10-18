#ifndef SANGUIS_LOAD_AURAS_CONTEXT_HPP_INCLUDED
#define SANGUIS_LOAD_AURAS_CONTEXT_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/load/auras/context_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace load
{
namespace auras
{

class context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		sanguis::load::resource::textures const &
	);

	~context();

	sge::texture::const_part_shared_ptr
	texture(
		sanguis::aura_type
	);
private:
	// TODO: We need a has for enums
	typedef
	std::map<
		sanguis::aura_type,
		sge::texture::const_part_shared_ptr
	>
	texture_map;

	texture_map textures_;
};

}
}
}

#endif
