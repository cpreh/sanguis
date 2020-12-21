#ifndef SANGUIS_CLIENT_LOAD_AURAS_CONTEXT_HPP_INCLUDED
#define SANGUIS_CLIENT_LOAD_AURAS_CONTEXT_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <sanguis/client/load/resource/textures_cref.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
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
	FCPPT_NONMOVABLE(
		context
	);
public:
	explicit
	context(
		sanguis::client::load::resource::textures_cref
	);

	~context();

	[[nodiscard]]
	sge::texture::part const &
	texture(
		sanguis::aura_type
	);
private:
	using
	texture_map
	=
	std::unordered_map<
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
