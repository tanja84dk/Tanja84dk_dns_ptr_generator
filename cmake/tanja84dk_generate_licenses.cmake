set(${PROJECT_NAME}_LICENSES_MACRO_FILE ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}_licenses_macro.h.in)

string(TOUPPER ${PROJECT_NAME} ${PROJECT_NAME}_MACRO_NAME)

function(tanja84dk_generate_license_begin)
    if(EXISTS "${${PROJECT_NAME}_LICENSES_MACRO_FILE}")
        file(WRITE "${${PROJECT_NAME}_LICENSES_MACRO_FILE}" "")
    endif()

    file(APPEND "${${PROJECT_NAME}_LICENSES_MACRO_FILE}" "#ifndef ${${PROJECT_NAME}_MACRO_NAME}_LICENCES_MACRO_H\n")
    file(APPEND "${${PROJECT_NAME}_LICENSES_MACRO_FILE}" "#define ${${PROJECT_NAME}_MACRO_NAME}_LICENCES_MACRO_H\n\n")    
endfunction(tanja84dk_generate_license_begin)





function(tanja84dk_generate_license ADDED_LIBRARY_NAME)

if(EXISTS "${${ADDED_LIBRARY_NAME}_SOURCE_DIR}/LICENSE")
    file(STRINGS ${${ADDED_LIBRARY_NAME}_SOURCE_DIR}/LICENSE TEMP_LICENSE)
    string(PREPEND TEMP_LICENSE "R\"(")
    string(APPEND TEMP_LICENSE ")\"")
    file(APPEND ${${PROJECT_NAME}_LICENSES_MACRO_FILE} "#define ${ADDED_LIBRARY_NAME}_LICENSE @${ADDED_LIBRARY_NAME}_LICENSE@\n")
    set(${ADDED_LIBRARY_NAME}_LICENSE "${TEMP_LICENSE}" PARENT_SCOPE)
else()
    message("${ADDED_LIBRARY_NAME}_LICENSE is missing\nLooked in: ${${ADDED_LIBRARY_NAME}_SOURCE_DIR}")
endif()
    
endfunction(tanja84dk_generate_license)


function(tanja84dk_generate_license_manual ADDED_LIBRARY_NAME LICENSE_PATH)

if(EXISTS "${LICENSE_PATH}")
    file(STRINGS ${LICENSE_PATH} TEMP_LICENSE)
    string(PREPEND TEMP_LICENSE "R\"(")
    string(APPEND TEMP_LICENSE ")\"")
    file(APPEND ${${PROJECT_NAME}_LICENSES_MACRO_FILE} "#define ${ADDED_LIBRARY_NAME}_LICENSE @${ADDED_LIBRARY_NAME}_LICENSE@\n")
    set(${ADDED_LIBRARY_NAME}_LICENSE "${TEMP_LICENSE}" PARENT_SCOPE)
else()
    message("${ADDED_LIBRARY_NAME}_LICENSE is missing\nLooked in ${LICENSE_PATH}")
endif()
    
endfunction(tanja84dk_generate_license_manual)



function(tanja84dk_generate_license_end)
    file(APPEND "${${PROJECT_NAME}_LICENSES_MACRO_FILE}"
    "\n#endif // TANJA84DK_DOCKERLIB_LICENCES_MACRO_H\n")
endfunction(tanja84dk_generate_license_end)

