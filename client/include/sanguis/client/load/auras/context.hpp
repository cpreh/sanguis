#ifndef SANGUIS_CLIENT_LOAD_AURAS_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_AURAS_CONTEXT_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/client/load/resource/textures_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
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
		sanguis::client::load::resource::textures const &
	);

	~context();

	sge::texture::part const &
	texture(
		sanguis::aura_type
	);
private:
	// TODO: We need a hash for enums
	using
	texture_map
	=
	std::map<
		sanguis::aura_type,
		fcppt::reference<
			sge::texture::part const
		>
	>;

	texture_map const textures_;
};

}
}
}
}

#endif
