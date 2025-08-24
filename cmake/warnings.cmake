
function(apply_project_warnings target)
  if (MSVC)
    target_compile_options(${target} PRIVATE /W4)
  else()
    target_compile_options(${target} PRIVATE
      -Wall -Wextra -Wpedantic
      -Wconversion -Wsign-conversion
      -Wshadow -Wduplicated-cond -Wduplicated-branches
      -Wlogical-op -Wnull-dereference -Wformat=2
    )
    if (ENABLE_WARNINGS_AS_ERRORS)
      target_compile_options(${target} PRIVATE -Werror)
    endif()
  endif()
endfunction()
