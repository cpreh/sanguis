#include <sanguis/aura_type.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/load/auras/context.hpp>
#include <sanguis/load/auras/lookup_name.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::load::auras::context::context(
	sanguis::load::resource::textures const &_resources
)
:
	textures_()
{
	for(
		boost::filesystem::directory_iterator it(
			sanguis::media_path()
			/
			FCPPT_TEXT("auras")
		);
		it != boost::filesystem::directory_iterator();
		++it
	)
	{
		boost::filesystem::path const path(
			it->path()
		);

		textures_.insert(
			std::make_pair(
				sanguis::load::auras::lookup_name(
					fcppt::filesystem::stem(
						path
					)
				),
				_resources.load(
					path
				)
			)
		);
	}

}

sanguis::load::auras::context::~context()
{
}

sge::texture::const_part_shared_ptr
sanguis::load::auras::context::texture(
	sanguis::aura_type const _aura_type
)
{
	texture_map::const_iterator const it(
		textures_.find(
			_aura_type
		)
	);

	FCPPT_ASSERT_ERROR(
		it != textures_.end()
	);

	return
		it->second;
}
