function(apply_project_warnings target)
  if (MSVC)
    target_compile_options(${target} PRIVATE /W4 /permissive- /EHsc)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${target} PRIVATE
      -Wall -Wextra -Wpedantic
      -Wconversion -Wsign-conversion
      -Wshadow
      -Wduplicated-cond -Wduplicated-branches
      -Wlogical-op
      -Wnull-dereference
      -Wformat=2
    )
  elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${target} PRIVATE
      -Wall -Wextra -Wpedantic
      -Wconversion -Wsign-conversion
      -Wshadow
      -Wnull-dereference
      -Wformat=2
      # safety: don't fail if a future CI clang doesn't know a flag
      -Wno-unknown-warning-option
    )
  endif()

  if (ENABLE_WARNINGS_AS_ERRORS)
    if (MSVC)
      target_compile_options(${target} PRIVATE /WX)
    else()
      target_compile_options(${target} PRIVATE -Werror)
    endif()
  endif()
endfunction()
