#include <sanguis/creator/generate.hpp>
#include <sanguis/creator/generators.hpp>
#include <sanguis/creator/min.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/creator/top_parameters.hpp>
#include <sanguis/creator/top_result.hpp>
#include <sanguis/tiles/area_container_ref.hpp>
#include <sanguis/tiles/cell.hpp>
#include <sanguis/tiles/cell_container.hpp>
#include <sanguis/tiles/collection.hpp>
#include <sanguis/tiles/draw.hpp>
#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/error_image.hpp>
#include <sanguis/tiles/log.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/store/srgba8.hpp>
#include <sge/image2d/store/view.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/main.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_input.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/enum/array.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_unsigned.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/help_result.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_optional.hpp>
#include <fcppt/options/no_default_value.hpp>
#include <fcppt/options/option.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace
{

FCPPT_RECORD_MAKE_LABEL(generator_name_label);

FCPPT_RECORD_MAKE_LABEL(output_path_label);

FCPPT_RECORD_MAKE_LABEL(seed_label);

using argument_record = fcppt::record::object<
    fcppt::record::element<generator_name_label, sanguis::creator::name>,
    fcppt::record::element<output_path_label, fcppt::string>,
    fcppt::record::element<seed_label, fcppt::optional::object<sanguis::creator::seed>>>;

void execute_main(argument_record const &_args)
{
  sge::systems::instance<sge::systems::with_image2d> const sys(
      sge::systems::make_list(sge::systems::image2d(sge::media::optional_extension_set())));

  sanguis::creator::top_result const result{
      sanguis::creator::generate(sanguis::creator::top_parameters{
          sys.log_context(),
          fcppt::record::get<generator_name_label>(_args),
          fcppt::optional::from(
              fcppt::record::get<seed_label>(_args),
              [] { return fcppt::random::generator::seed_from_chrono<sanguis::creator::seed>(); }),
          fcppt::enum_::array_init<sanguis::creator::opening_count_array>(
              [](sanguis::creator::opening_type) { return sanguis::creator::opening_count{0U}; }),
          sanguis::creator::spawn_boss{false}})};

  sanguis::tiles::collection tile_collection{fcppt::make_ref(sys.image_system())};

  sanguis::tiles::log const tiles_log{sys.log_context()};

  sanguis::tiles::cell_container const cells{sanguis::tiles::draw(
      tiles_log,
      result.grid(),
      result.background_grid(),
      fcppt::make_ref(tile_collection),
      sanguis::creator::min{fcppt::math::vector::null<sanguis::creator::pos>()},
      sanguis::creator::sup{fcppt::math::dim::to_vector(result.grid().size())})};

  using store_type = sge::image2d::store::srgba8;

  store_type store{
      result.grid().size() * sanguis::creator::tile_size::value,
      store_type::mizuiro_color(
          (sge::image::color::init::red() %= 0.)(sge::image::color::init::green() %= 0.)(
              sge::image::color::init::blue() %= 1.)(sge::image::color::init::alpha() %= 1.))};

  using path_file_map = std::map<std::filesystem::path, sge::image2d::file_unique_ptr>;

  path_file_map files{};

  using error_image_array = fcppt::enum_::array<sanguis::tiles::error, sge::image2d::store::object>;

  auto const error_images(fcppt::enum_::array_init<error_image_array>(
      [](sanguis::tiles::error const _error) { return sanguis::tiles::error_image(_error); }));

  for (sanguis::tiles::cell const &cell : cells)
  {
    auto const dest_pos(
        fcppt::math::vector::structure_cast<sge::image2d::rect::vector, fcppt::cast::size_fun>(
            fcppt::math::vector::to_unsigned(cell.pos())));

    fcppt::variant::match(
        cell.content(),
        [&store, &cell, &files, &sys, dest_pos](
            sanguis::tiles::area_container_ref const &_container)
        {
          sge::image2d::view::const_object const source_view(sge::image2d::view::checked_sub(
              fcppt::container::get_or_insert(
                  files,
                  cell.path().get(),
                  [&sys](std::filesystem::path const &_path)
                  {
                    return fcppt::optional::to_exception(
                        sge::image2d::load(fcppt::make_ref(sys.image_system()), _path),
                        [] {
                          return fcppt::exception{
                              FCPPT_TEXT("Cannot load path!")};
                        });
                  })
                  ->view(),
              fcppt::optional::to_exception(
                  fcppt::container::maybe_front(_container.get()),
                  [] {
                    return fcppt::exception{FCPPT_TEXT("Container is empty!")};
                  })
                  .get()));

          sge::image2d::algorithm::copy_and_convert(
              source_view,
              sge::image2d::view::checked_sub(
                  sge::image2d::view::object{store.wrapped_view()},
                  sge::image2d::rect{dest_pos, sge::image2d::view::size(source_view)}),
              sge::image::algorithm::may_overlap::no,
              sge::image::algorithm::uninitialized::no);
        },
        [&store, &error_images, dest_pos](sanguis::tiles::error const _error)
        {
          sge::image2d::view::const_object const source_view(
              sge::image2d::store::view(fcppt::make_cref(error_images[_error])));

          sge::image2d::algorithm::copy_and_convert(
              source_view,
              sge::image2d::view::checked_sub(
                  sge::image2d::view::object{store.wrapped_view()},
                  sge::image2d::rect{dest_pos, sge::image2d::view::size(source_view)}),
              sge::image::algorithm::may_overlap::no,
              sge::image::algorithm::uninitialized::no);
        });
  }

  sge::image2d::save_from_view(
      sys.image_system(),
      sge::image2d::view::const_object{store.const_wrapped_view()},
      std::filesystem::path(fcppt::record::get<output_path_label>(_args)));
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int FCPPT_MAIN(int argc, fcppt::args_char **argv)
try
{
  auto const parser{fcppt::options::apply(
      fcppt::options::argument<generator_name_label, sanguis::creator::name>{
          fcppt::options::long_name{FCPPT_TEXT("generator-name")},
          fcppt::options::optional_help_text{}},
      fcppt::options::argument<output_path_label, fcppt::string>{
          fcppt::options::long_name{FCPPT_TEXT("output-file")},
          fcppt::options::optional_help_text{
              fcppt::options::help_text{FCPPT_TEXT("Path to the output file.")}}},
      fcppt::options::make_optional(fcppt::options::option<seed_label, sanguis::creator::seed>{
          fcppt::options::optional_short_name{},
          fcppt::options::long_name{FCPPT_TEXT("seed")},
          fcppt::options::no_default_value<sanguis::creator::seed>(),
          fcppt::options::optional_help_text{fcppt::options::help_text{
              FCPPT_TEXT("The seed to use. If not specified, a random seed is used.")}}}))};

  using result_type = fcppt::options::result_of<decltype(parser)>;

  fcppt::options::help_result<result_type> const result{fcppt::options::parse_help(
      fcppt::options::default_help_switch(), parser, fcppt::args_from_second(argc, argv))};

  return fcppt::variant::match(
      result,
      [](fcppt::options::result<result_type> const &_result)
      {
        return fcppt::either::match(
            _result,
            [](fcppt::options::error const &_error)
            {
              fcppt::io::cerr() << _error << FCPPT_TEXT('\n');

              return EXIT_FAILURE;
            },
            [](result_type const &_args)
            {
              execute_main(fcppt::record::permute<argument_record>(_args));

              return EXIT_SUCCESS;
            });
      },
      [](fcppt::options::help_text const &_help_text)
      {
        fcppt::io::cout() << _help_text << FCPPT_TEXT("\n\n")
                          << FCPPT_TEXT("Available generators are: ")
                          << fcppt::container::output(sanguis::creator::generators())
                          << FCPPT_TEXT('\n');

        return EXIT_SUCCESS;
      });
}
catch (fcppt::exception const &_exception)
{
  fcppt::io::cerr() << _exception.string() << FCPPT_TEXT('\n');

  return EXIT_FAILURE;
}
catch (std::exception const &_exception)
{
  std::cerr << _exception.what() << '\n';

  return EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
