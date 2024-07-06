fcppt_utils_load_source_files(core/files.txt SANGUIS_CORE_FILES)

sanguis_add_library(core "${SANGUIS_CORE_FILES}" DEPS ${sgeconfig_TARGET}
                    ${fcppt_core_TARGET} ${fcppt_log_TARGET})
