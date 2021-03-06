# CopySharedLibraries.cmake
#
# Copies necessary DLLs to a target's location and sets up propery dependencies 
function(copy_shared_libraries target_name target_location)
    if(WIN32)
        if(EXISTS ${BLAS_DLL_DIR})
            set(command_target_name copy_dlls_to_${target_name})
            foreach(blas_dll ${BLAS_DLLS})
                add_custom_command(TARGET ${target_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${target_location}
                    COMMAND ${CMAKE_COMMAND} -E echo "Copying DLL ${BLAS_DLL_DIR}/${blas_dll} to ${target_location}"
                    COMMAND ${CMAKE_COMMAND} -E copy ${BLAS_DLL_DIR}/${blas_dll} ${target_location}
                )
            endforeach()
        endif()
    endif()
endfunction()
