# cmake/clang_tidy.cmake
function(enable_tidy TARGET)
  if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (CLANG_TIDY_EXE)
      set(tidy_args
        "${CLANG_TIDY_EXE}"
        "-p=${CMAKE_BINARY_DIR}"
        "-header-filter=^(src|tests)/.*"
        # uncomment next line to force errors only for selected checks:
        # "-warnings-as-errors=bugprone-*,performance-*,modernize-*"
      )
      set_property(TARGET ${TARGET} PROPERTY CXX_CLANG_TIDY "${tidy_args}")
    endif()
  endif()
endfunction()
