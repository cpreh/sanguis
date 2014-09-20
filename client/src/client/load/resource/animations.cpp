#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/client/load/first_file.hpp>
#include <sanguis/client/load/log.hpp>
#include <sanguis/client/load/next_file.hpp>
#include <sanguis/client/load/resource/animations.hpp>
#include <sanguis/client/load/resource/textures.hpp>
#include <sanguis/client/load/resource/animation/entity.hpp>
#include <sanguis/client/load/resource/animation/entity_vector.hpp>
#include <sanguis/client/load/resource/animation/series.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <chrono>
#include <cstddef>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::load::resource::animation::series const &
sanguis::client::load::resource::animations::load(
	boost::filesystem::path const &_dir
) const
{
	return
		fcppt::container::get_or_insert(
			animations_,
			_dir,
			std::bind(
				&sanguis::client::load::resource::animations::do_load,
				this,
				std::placeholders::_1
			)
		);
}

sanguis::client::load::resource::animations::animations(
	sanguis::client::load::resource::textures &_textures
)
:
	textures_(
		_textures
	),
	animations_()
{
}

sanguis::client::load::resource::animations::~animations()
{
}

// TODO: Rewrite this!
sanguis::client::load::resource::animation::series
sanguis::client::load::resource::animations::do_load(
	boost::filesystem::path const &_dir
) const
{
	if(
		!boost::filesystem::exists(
			_dir
		)
		||
		!boost::filesystem::is_directory(
			_dir
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("directory for animation \"")
			+
			fcppt::filesystem::path_to_string(
				_dir
			)
			+
			FCPPT_TEXT("\" doesn't exist")
		);

	boost::filesystem::path const framesfile(
		_dir
		/
		FCPPT_TEXT("frames")
	);

	// look for frames file inside directory
	if(
		!boost::filesystem::exists(
			framesfile
		)
		||
		!boost::filesystem::is_regular_file(
			framesfile
		)
	)
		return
			this->load_without_frames_file(
				_dir
			);

	// and parse line by line
	fcppt::io::ifstream file(
		framesfile
	);

	if(
		!file.is_open()
	)
		throw sanguis::exception(
			FCPPT_TEXT("error opening file \"")
			+
			fcppt::filesystem::path_to_string(
				framesfile
			)
			+
			FCPPT_TEXT("\""));

	// read first line, determine if it has constant frame time
	fcppt::string line;

	if(
		!std::getline(
			file,
			line
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("unexpected end of file \"")
			+
			fcppt::filesystem::path_to_string(
				framesfile
			)
		);

	fcppt::optional<
		sanguis::duration
	> const_delay;

	if(
		boost::algorithm::starts_with(
			line,
			FCPPT_TEXT("frame_length ")
		)
	)
		const_delay =
			std::chrono::duration_cast<
				sanguis::duration
			>(
				std::chrono::milliseconds(
					fcppt::extract_from_string_exn<
						std::int_least64_t
					>(
						line.substr(
							fcppt::string(
								FCPPT_TEXT("frame_length ")
							)
							.length()
						)
					)
				)
			);
	else
		file.seekg(
			0,
			std::ios_base::beg
		);

	sanguis::client::load::resource::animation::entity_vector anim;

	unsigned lineno(
		const_delay
		?
			2
		:
			1
	);

	while(
		std::getline(
			file,
			line
		)
	)
	{
		boost::algorithm::trim(
			line
		);

		if(
			line.empty()
		)
			continue;

		sanguis::duration delay(
			0
		);

		fcppt::string filename(
			line
		);

		if(
			!const_delay
		)
		{
			fcppt::io::istringstream ss(
				line
			);

			std::int_least64_t temp_delay;

			if(
				!(
					ss >> temp_delay >> std::ws
				)
			)
				throw sanguis::exception(
					FCPPT_TEXT("invalid line ")
					+
					fcppt::insert_to_fcppt_string(
						lineno
					)
					+
					FCPPT_TEXT(" in animation ")
					+
					fcppt::filesystem::path_to_string(
						_dir
					)
				);

			filename =
				ss.str().substr(
					static_cast<
						fcppt::string::size_type
					>(
						ss.tellg()
					)
				);
			delay =
				std::chrono::duration_cast<
					sanguis::duration
				>(
					std::chrono::milliseconds(
						temp_delay
					)
				);
		}
		else
		{
			delay = *const_delay;
		}

		anim.push_back(
			sanguis::client::load::resource::animation::entity(
				delay,
				this->load_texture(
					_dir
					/
					filename
				)
			)
		);

		++lineno;
	}

	return
		sanguis::client::load::resource::animation::series(
			std::move(
				anim
			)
		);
}

sge::texture::const_part_unique_ptr
sanguis::client::load::resource::animations::load_texture(
	boost::filesystem::path const &_path
) const
{
	return
		textures_.do_load_inner(
			_path
		);
}

sanguis::client::load::resource::animation::series
sanguis::client::load::resource::animations::load_without_frames_file(
	boost::filesystem::path const &_dir
) const
{
	boost::filesystem::directory_iterator const first_file(
		sanguis::client::load::first_file(
			_dir
		)
	);

	if(
		first_file
		==
		boost::filesystem::directory_iterator()
	)
		throw sanguis::exception(
			fcppt::filesystem::path_to_string(
				_dir
			)
			+
			FCPPT_TEXT(" is empty!")
		);

	boost::filesystem::path const first_path(
		*first_file
	);

	if(
		sanguis::client::load::next_file(
			first_file
		)
		!=
		boost::filesystem::directory_iterator()
	)
		FCPPT_LOG_WARNING(
			sanguis::client::load::log(),
			fcppt::log::_
				<< FCPPT_TEXT("No frames file found in \"")
				<< fcppt::filesystem::path_to_string(
					_dir
				)
				<< FCPPT_TEXT("\" although there is more than one file!")
				<< FCPPT_TEXT(" Just taking the first image.")
		);

	return
		sanguis::client::load::resource::animation::series(
			fcppt::assign::make_container<
				sanguis::client::load::resource::animation::entity_vector
			>(
				sanguis::client::load::resource::animation::entity(
					sanguis::duration_second(
						1.f
					),
					this->load_texture(
						first_path
					)
				)
			)
		);
}
