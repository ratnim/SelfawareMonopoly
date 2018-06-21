include(cmake/Cppcheck.cmake)

set(OPTION_CPPCHECK_ENABLED Off)

# Function to register a target for enabled health checks
function(perform_health_checks target)
    if(NOT TARGET check-all)
        add_custom_target(check-all)
    
        set_target_properties(check-all
            PROPERTIES
            FOLDER "Maintenance"
            EXCLUDE_FROM_DEFAULT_BUILD 1
        )
    endif()
    
    add_custom_target(check-${target})
    
    set_target_properties(check-${target}
        PROPERTIES
        FOLDER "Maintenance"
        EXCLUDE_FROM_DEFAULT_BUILD 1
    )
    
    if (OPTION_CPPCHECK_ENABLED)
        perform_cppcheck(cppcheck-${target} ${target} ${ARGN})
        add_dependencies(check-${target} cppcheck-${target})
    endif()
    
    add_dependencies(check-all check-${target})
endfunction()

# Enable or disable cppcheck for health checks
function(enable_cppcheck status)
    if(NOT ${status})
        set(OPTION_CPPCHECK_ENABLED ${status} PARENT_SCOPE)
        message(STATUS "Check cppcheck skipped: Manually disabled")
        
        return()
    endif()
    
    find_package(cppcheck)
    
    if(NOT cppcheck_FOUND)
        set(OPTION_CPPCHECK_ENABLED Off PARENT_SCOPE)
        message(STATUS "Check cppcheck skipped: cppcheck not found")
        
        return()
    endif()
    
    set(OPTION_CPPCHECK_ENABLED ${status} PARENT_SCOPE)
    message(STATUS "Check cppcheck")
endfunction()
