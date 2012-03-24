#include <sanguis/load/resource/animations.hpp>
#include <sanguis/load/resource/textures.hpp>
#include <sanguis/load/resource/map_get_or_create.hpp>
#include <sanguis/load/first_file.hpp>
#include <sanguis/load/log.hpp>
#include <sanguis/load/next_file.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/exception.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::load::resource::animation::series const
sanguis::load::resource::animations::load(
	boost::filesystem::path const &dir) const
{
	return map_get_or_create(
		animations_,
		dir,
		std::tr1::bind(
			&animations::do_load,
			this,
			std::tr1::placeholders::_1
		)
	);
}

sanguis::load::resource::animations::animations(
	textures &_textures
)
:
	textures_(_textures)
{
}

sanguis::load::resource::animations::~animations()
{
}

sanguis::load::resource::animation::series const
sanguis::load::resource::animations::do_load(
	boost::filesystem::path const &dir) const
{
	if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir))
		throw exception(
			FCPPT_TEXT("directory for animation \"")
			+ fcppt::filesystem::path_to_string(
				dir
			)
			+ FCPPT_TEXT("\" doesn't exist")
		);

	boost::filesystem::path const framesfile = dir / FCPPT_TEXT("frames");

	// look for frames file inside directory
	if (!boost::filesystem::exists(framesfile) || !boost::filesystem::is_regular_file(framesfile))
		return load_without_frames_file(dir);
	//
	// and parse line by line
	fcppt::io::ifstream file(framesfile);
	if (!file.is_open())
		throw exception(
			FCPPT_TEXT("error opening file \"")
			+ fcppt::filesystem::path_to_string(
				framesfile
			)
			+ FCPPT_TEXT("\""));

	// read first line, determine if it has constant frame time
	fcppt::string line;
	if (!std::getline(file,line))
		throw exception(
			FCPPT_TEXT("unexpected end of file \"")
			+ fcppt::filesystem::path_to_string(
				framesfile
			)
		);

	fcppt::optional<
		sanguis::duration
	> const_delay;

	if (boost::algorithm::starts_with(line,FCPPT_TEXT("frame_length ")))
		const_delay =
			boost::chrono::duration_cast<
				sanguis::duration
			>(
				boost::chrono::milliseconds(
					fcppt::extract_from_string_exn<
						boost::int_least64_t
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
		file.seekg(0, std::ios_base::beg);

	animation::series anim;

	unsigned lineno = const_delay ? 2 : 1;
	while (std::getline(file,line))
	{
		boost::algorithm::trim(line);

		if (line.empty())
			continue;

		sanguis::duration delay(0);
		fcppt::string filename = line;

		if (!const_delay)
		{
			fcppt::io::istringstream ss(line);
			boost::int_least64_t temp_delay;
			ss >> temp_delay >> std::ws;

			if (!ss)
				throw sanguis::exception(
					FCPPT_TEXT("invalid line ")
					+ fcppt::insert_to_fcppt_string(
						lineno
					)
					+ FCPPT_TEXT(" in animation ")
					+ fcppt::filesystem::path_to_string(
						dir
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
				boost::chrono::duration_cast<
					sanguis::duration
				>(
					boost::chrono::milliseconds(
						temp_delay
					)
				);
		}
		else
		{
			delay = *const_delay;
		}

		anim.push_back(
			animation::entity(
				delay,
				load_texture(
					dir / filename
				)
			)
		);

		++lineno;
	}

	return anim;
}

sge::texture::const_part_ptr const
sanguis::load::resource::animations::load_texture(
	boost::filesystem::path const &p) const
{
	return textures_.do_load_inner(p);
}

sanguis::load::resource::animation::series const
sanguis::load::resource::animations::load_without_frames_file(
	boost::filesystem::path const &dir) const
{
	boost::filesystem::directory_iterator const first_file(
		sanguis::load::first_file(
			dir));

	if(first_file == boost::filesystem::directory_iterator())
		throw sanguis::exception(
			fcppt::filesystem::path_to_string(
				dir
			)
			+ FCPPT_TEXT(" is empty!")
		);

	boost::filesystem::path const first_path(
		*first_file);

	if(sanguis::load::next_file(first_file) != boost::filesystem::directory_iterator())
		FCPPT_LOG_WARNING(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("No frames file found in \"")
				<< fcppt::filesystem::path_to_string(
					dir
				)
				<< FCPPT_TEXT("\" although there is more than one file!")
				<< FCPPT_TEXT(" Just taking the first image."));

	animation::series ret;
	ret.push_back(
		animation::entity(
			sanguis::duration_second(
				1.f
			),
			load_texture(first_path)
		)
	);
	return ret; // TODO: can we do this with boost::assign?
}
