#include <sanguis/model/serialize.hpp>
#include <sanguis/tools/libmergeimage/merge_images.hpp>
#include <sanguis/tools/libmergeimage/merge_result.hpp>
#include <sanguis/tools/libmergeimage/save_images.hpp>
#include <sanguis/tools/libmergeimage/saved_image_vector.hpp>
#include <sanguis/tools/libmergeimage/to_model.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/filesystem/normalize.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_result.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/record/variadic.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <fcppt/config/external_end.hpp>


namespace
{

FCPPT_RECORD_MAKE_LABEL(
	input_path_label
);

FCPPT_RECORD_MAKE_LABEL(
	output_file_label
);

typedef
fcppt::record::variadic<
	fcppt::record::element<
		input_path_label,
		fcppt::string
	>,
	fcppt::record::element<
		output_file_label,
		fcppt::string
	>
>
argument_record;

void
execute_main(
	argument_record const &_args
)
{
	sge::systems::instance<
		brigand::list<
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::image2d(
				sge::media::optional_extension_set()
			)
		)
	);

	sanguis::tools::libmergeimage::merge_result const result(
		sanguis::tools::libmergeimage::merge_images(
			sys.image_system(),
			fcppt::filesystem::normalize(
				std::filesystem::path(
					fcppt::record::get<
						input_path_label
					>(
						_args
					)
				)
			)
		)
	);

	std::filesystem::path const output_path(
		fcppt::filesystem::normalize(
			std::filesystem::path(
				fcppt::record::get<
					output_file_label
				>(
					_args
				)
			)
		)
	);

	sanguis::tools::libmergeimage::saved_image_vector const saved_images(
		sanguis::tools::libmergeimage::save_images(
			sys.image_system(),
			output_path,
			result.images()
		)
	);

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
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char **argv
)
try
{
	auto const parser{
		fcppt::options::apply(
			fcppt::options::argument<
				input_path_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("input-path")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Path where the input files are.")
					}
				}
			},
			fcppt::options::argument<
				output_file_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("output-file")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Path to the output file.")
					}
				}
			}
		)
	};

	typedef
	fcppt::options::result_of<
		decltype(
			parser
		)
	>
	result_type;

	fcppt::options::help_result<
		result_type
	> const result{
		fcppt::options::parse_help(
			fcppt::options::default_help_switch(),
			parser,
			fcppt::args_from_second(
				argc,
				argv
			)
		)
	};

	return
		fcppt::variant::match(
			result,
			[](
				fcppt::options::result<
					result_type
				> const &_result
			)
			{
				return
					fcppt::either::match(
						_result,
						[](
							fcppt::options::error const &_error
						)
						{
							fcppt::io::cerr()
								<<
								_error
								<<
								FCPPT_TEXT('\n');

							return
								EXIT_FAILURE;
						},
						[](
							result_type const &_args
						)
						{
							execute_main(
								fcppt::record::permute<
									argument_record
								>(
									_args
								)
							);

							return
								EXIT_SUCCESS;
						}
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				fcppt::io::cout()
					<<
					_help_text
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_SUCCESS;
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<<
		_error.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<<
		_error.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
