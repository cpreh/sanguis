#include <sanguis/media_path.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/tiles/category.hpp>
#include <sanguis/client/load/tiles/const_optional_texture_container_ref.hpp>
#include <sanguis/client/load/tiles/decode_name.hpp>
#include <sanguis/client/load/tiles/make_textures.hpp>
#include <sanguis/client/load/tiles/name.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::tiles::set::set(
	sanguis::client::load::resource::textures const &_textures,
	sanguis::client::load::tiles::category const &_category,
	sanguis::client::load::tiles::name const &_name
)
:
	sanguis::client::load::tiles::set(
		_textures,
		sanguis::media_path()
		/
		FCPPT_TEXT("tiles")
		/
		_category.get()
		/
		_name.get()
	)
{
}

sanguis::client::load::tiles::set::set(
	set &&
) = default;

sanguis::client::load::tiles::set &
sanguis::client::load::tiles::set::operator=(
	set &&
) = default;

sanguis::client::load::tiles::set::~set()
{
}

sanguis::client::load::tiles::set::set(
	sanguis::client::load::resource::textures const &_textures,
	boost::filesystem::path const &_path
)
:
	texture_{
		_textures.load_opt(
			_path
			/
			FCPPT_TEXT("texture.png")
		)
	},
	elements_{
		fcppt::maybe(
			texture_,
			[]{
				return
					element_map();
			},
			[
				&_path
			](
				sge::texture::part const &_texture
			)
			{
				return
					fcppt::algorithm::map_optional<
						element_map
					>(
						sge::parse::json::parse_file_exn(
							_path
							/
							FCPPT_TEXT("mapping.json")
						).object().members,
						[
							&_texture
						](
							sge::parse::json::member const &_member
						)
						{
							return
								fcppt::optional_bind_construct(
									sanguis::client::load::tiles::decode_name(
										_member.first
									),
									[
										&_texture,
										&_member
									](
										sanguis::client::load::tiles::orientation const &_orientation
									)
									{
										return
											std::make_pair(
												_orientation,
												sanguis::client::load::tiles::make_textures(
													_texture,
													_member.second
												)
											);
									}
								);
						}
					);
			}
		)
	}
{
}

sanguis::client::load::tiles::const_optional_texture_container_ref
sanguis::client::load::tiles::set::orientation(
	sanguis::client::load::tiles::orientation const &_orientation
) const
{
	return
		fcppt::container::find_opt(
			elements_,
			_orientation
		);
}
