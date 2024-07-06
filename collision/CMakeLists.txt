fcppt_utils_load_source_files(collision/files.txt SANGUIS_COLLISION_FILES)

sanguis_add_library(
  collision
  "${SANGUIS_COLLISION_FILES}"
  HAS_IMPL_DIR
  DEPS
  ${sanguis_creator_TARGET}
  ${sanguis_core_TARGET}
  fcppt_boost_interface
  ${fcppt_core_TARGET}
  ${fcppt_log_TARGET}
  TRANSITIVE_DEPS
  sanguis_creator_interface
  fcppt_core_interface
  fcppt_log_interface)

add_subdirectory(bench)
