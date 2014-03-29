#include <sanguis/tools/libmergeimage/image.hpp>
#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/merge_images.hpp>
#include <sanguis/tools/libmergeimage/path.hpp>
#include <sanguis/tools/libmergeimage/path_to_string.hpp>
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
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/ofstream.hpp>
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

	sanguis::tools::libmergeimage::image_vector const result(
		sanguis::tools::libmergeimage::merge_images(
			sys.image_system(),
			boost::filesystem::path(
				argv[1]
			)
		)
	);

	boost::filesystem::path const output_path(
		argv[2]
	);

	for(
		sanguis::tools::libmergeimage::image_vector::size_type index(
			0u
		);
		index < result.size();
		++index
	)
	{
		sanguis::tools::libmergeimage::image const &image(
			result[
				index
			]
		);

		fcppt::string const index_string(
			fcppt::insert_to_fcppt_string(
				index
			)
		);

		sge::image2d::save_from_view(
			sys.image_system(),
			sge::image2d::view::const_object(
				image.store().wrapped_view()
			),
			output_path
			/
			(
				index_string
				+
				FCPPT_TEXT(".png")
			)
		);

		// TODO: Just for testing
		fcppt::io::ofstream stream(
			output_path
			/
			(
				index_string
				+
				FCPPT_TEXT(".txt")
			)
		);

		if(
			!stream.is_open()
		)
		{
			fcppt::io::cerr()
				<< FCPPT_TEXT("Can't open text file\n");

			return
				EXIT_FAILURE;
		}

		for(
			sanguis::tools::libmergeimage::path const &path
			:
			image.paths()
		)
			stream
				<<
				sanguis::tools::libmergeimage::path_to_string(
					path
				)
				<<
				FCPPT_TEXT('\n');
	}

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
