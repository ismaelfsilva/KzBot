cmake_minimum_required(VERSION 3.5)

project(KzBot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.5.1/msvc2019_64" ${CMAKE_PREFIX_PATH})
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS LinguistTools)
find_package(OpenSSL REQUIRED)

set(PROJECT_SOURCES
        main.cpp

        Util/Enums.h

        Settings/globals.h
        Settings/globals.cpp


        Settings/actionsettings.h Settings/actionsettings.cpp
        Settings/comborule.h Settings/comborule.cpp

        UI/loginwindow.cpp
        UI/loginwindow.h
        UI/loginwindow.ui

        UI/mainwindow.cpp
        UI/mainwindow.h
        UI/mainwindow.ui

        UI/healer.cpp
        UI/healer.h
        UI/healer.ui

        UI/toolstab.cpp
        UI/toolstab.h
        UI/toolstab.ui

        UI/confighelper.h UI/confighelper.cpp UI/confighelper.ui
        UI/configchooser.h UI/configchooser.cpp UI/configchooser.ui
        UI/pvptools.h UI/pvptools.cpp UI/pvptools.ui
        UI/partyhunt.h UI/partyhunt.cpp UI/partyhunt.ui

        UI/clientmanager.h
        UI/clientmanager.cpp
        UI/clientmanager.ui

        Addresses/hotkey.h Addresses/hotkey.cpp
        Addresses/chatmessage.h Addresses/chatmessage.cpp
        Addresses/chat.h Addresses/chat.cpp

        Addresses/player.cpp
        Addresses/player.h

        Addresses/battlelist.cpp
        Addresses/battlelist.h

        Addresses/client.cpp
        Addresses/client.h

        Addresses/creature.cpp
        Addresses/creature.h

        Addresses/cooldown.h Addresses/cooldown.cpp

        Addresses/Versions/versions.cpp
        Addresses/Versions/versions.h

        Objects/keybinding.h Objects/keybinding.cpp
        Objects/hotkey.h Objects/hotkey.cpp
        Objects/position.h Objects/position.cpp
        Objects/spell.h Objects/spell.cpp
        Objects/game.h Objects/game.cpp

        Objects/client.h Objects/client.cpp

        Objects/player.h
        Objects/player.cpp


        Objects/chatmessage.h Objects/chatmessage.cpp

        Objects/chat.h Objects/chat.cpp
        Objects/inventoryitem.h Objects/inventoryitem.cpp

        Objects/cooldown.h
        Objects/cooldown.cpp

        Objects/creature.h Objects/creature.cpp
        Objects/battlelist.h Objects/battlelist.cpp

        Settings/actionrule.h
        Settings/actionrule.cpp

        Settings/scriptconfig.h
        Settings/scriptconfig.cpp

        Util/kzhelper.h
        Util/kzhelper.cpp

        Threads/updater.h Threads/updater.cpp

        Threads/healer.h
        Threads/healer.cpp

        Threads/partyhunt.h
        Threads/partyhunt.cpp


        Threads/tools.h Threads/tools.cpp
        Threads/pvptools.h Threads/pvptools.cpp

        resources.qrc
        resources.rc
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(KzBot
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET KzBot APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(KzBot SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(KzBot
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Adicione o comando qt_add_lupdate aqui para gerar os arquivos .ts
qt_add_lupdate(KzBot
    TARGET_TRANSLATIONS ${CMAKE_CURRENT_BINARY_DIR}/translations/KzBot.ts
    SOURCES ${PROJECT_SOURCES}
)

target_link_libraries(KzBot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network OpenSSL::SSL OpenSSL::Crypto wininet)

set_target_properties(KzBot PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MSP PROPERTIES LINK_FLAGS  "/SUBSYSTEM:WINDOWS" # "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"
)


install(TARGETS KzBot
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(KzBot)
endif()
