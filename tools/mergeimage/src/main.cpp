#include <sanguis/model/image_name.hpp>
#include <sanguis/model/serialize.hpp>
#include <sanguis/tools/libmergeimage/image.hpp>
#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/merge_images.hpp>
#include <sanguis/tools/libmergeimage/merge_result.hpp>
#include <sanguis/tools/libmergeimage/saved_image.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sanguis/tools/libmergeimage/to_model.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/normalize.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char **argv
)
try
{
	if(
		argc
		!=
		3
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Usage: ")
			<< argv[0]
			<< FCPPT_TEXT(" <input-path> <output-path>\n");

		return
			EXIT_FAILURE;
	}

	sge::systems::instance<
		boost::mpl::vector1<
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::optional_extension_set()
			)
		)
	);

	sanguis::tools::libmergeimage::merge_result const result(
		sanguis::tools::libmergeimage::merge_images(
			sys.image_system(),
			fcppt::filesystem::normalize(
				boost::filesystem::path(
					argv[1]
				)
			)
		)
	);

	boost::filesystem::path const output_path(
		fcppt::filesystem::normalize(
			boost::filesystem::path(
				argv[2]
			)
		)
	);

	sanguis::tools::libmergeimage::saved_image_vector saved_images;

	for(
		sanguis::tools::libmergeimage::image_vector::size_type index(
			0u
		);
		index < result.images().size();
		++index
	)
	{
		sanguis::tools::libmergeimage::image const &image(
			result.images()[
				index
			]
		);

		fcppt::string const file_name(
			fcppt::insert_to_fcppt_string(
				index
			)
			+
			FCPPT_TEXT(".png")
		);

		sge::image2d::save_from_view(
			sys.image_system(),
			sge::image2d::view::const_object(
				image.store().wrapped_view()
			),
			output_path
			/
			file_name
		);

		saved_images.push_back(
			sanguis::tools::libmergeimage::saved_image(
				image.paths(),
				sanguis::model::image_name(
					file_name
				)
			)
		);
	}

	sanguis::model::serialize(
		output_path
		/
		(
			fcppt::filesystem::stem(
				output_path
			)
			+
			FCPPT_TEXT(".json")
		),
		sanguis::tools::libmergeimage::to_model(
			result.cell_size(),
			saved_images
		)
	);

	return
		EXIT_SUCCESS;
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return
		EXIT_FAILURE;
}
