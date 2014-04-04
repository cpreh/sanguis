#include <sanguis/tools/libmergeimage/exception.hpp>
#include <sanguis/tools/libmergeimage/image.hpp>
#include <sanguis/tools/libmergeimage/image_store.hpp>
#include <sanguis/tools/libmergeimage/aux_/best_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/fold_paths.hpp>
#include <sanguis/tools/libmergeimage/aux_/make_image.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_scoped_ptr.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::image
sanguis::tools::libmergeimage::aux_::make_image(
	sge::image2d::system &_image_system,
	boost::filesystem::path const &_base_path,
	sanguis::tools::libmergeimage::aux_::cell_size const _cell_size,
	sanguis::tools::libmergeimage::aux_::path_vector _paths
)
{
	std::sort(
		_paths.begin(),
		_paths.end()
	);

	sge::image::size_type const border_sz(
		sanguis::tools::libmergeimage::aux_::best_size(
			_paths.size(),
			_cell_size
		)
	);

	sanguis::tools::libmergeimage::image_store dest(
		fcppt::math::dim::fill<
			sanguis::tools::libmergeimage::image_store::dim::dim_wrapper::value
		>(
			border_sz
		)
	);

	sge::image2d::view::object const dest_view(
		dest.wrapped_view()
	);

	sge::image2d::algorithm::fill(
		dest_view,
		sge::image::color::predef::transparent()
	);

	sge::image2d::rect::vector pos(
		sge::image2d::rect::vector::null()
	);

	for(
		boost::filesystem::path const &suffix_path
		:
		_paths
	)
	{
		boost::filesystem::path const cur_path(
			_base_path
			/
			suffix_path
		);

		sge::image2d::file_scoped_ptr const img(
			sge::image2d::load_exn(
				_image_system,
				cur_path
			)
		);

		if(
			img->size()
			!=
			_cell_size.get()
		)
			throw
				sanguis::tools::libmergeimage::exception(
					FCPPT_TEXT("File ")
					+
					fcppt::filesystem::path_to_string(
						cur_path
					)
					+
					FCPPT_TEXT(" has dimensions ")
					+
					fcppt::insert_to_fcppt_string(
						img->size()
					)
					+
					FCPPT_TEXT(" but the cell size so far was ")
					+
					fcppt::insert_to_fcppt_string(
						_cell_size
					)
				);

		sge::image2d::algorithm::copy_and_convert(
			img->view(),
			sge::image2d::view::sub(
				dest_view,
				sge::image2d::rect(
					pos,
					_cell_size.get()
				)
			),
			sge::image::algorithm::may_overlap::no
		);

		pos.x() += _cell_size.get().w() + 1;

		if(
			pos.x() + _cell_size.get().w() + 1 > border_sz
		)
		{
			pos.x() = 0;
			pos.y() += _cell_size.get().h() + 1;
		}
	}

	return
		sanguis::tools::libmergeimage::image(
			sanguis::tools::libmergeimage::aux_::fold_paths(
				_paths
			),
			std::move(
				dest
			)
		);
}