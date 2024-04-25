cmake_minimum_required(VERSION 3.5)

project(packetsParser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        packetparser.cpp
        packetparser.h
        packetparser.ui
        PacketFactory.h
        PacketFactory.cpp
        PacketDataExtractor.h
        PacketDataExtractor.cpp
        Packet.h
        Packet.cpp
        OtherPacket.h
        OtherPacket.cpp
        IP_PacketData.h
        IP_Packet.h
        IP_Packet.cpp
        ICMP_Packet.h
        ICMP_PacketData.h
        ICMP_Packet.cpp
        BasePacketData.h
        ARP_Packet.cpp
        ARP_Packet.h
        ARP_PacketData.h
        PacketParserService.h
        PacketParserService.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(packetsParser
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        customExceptions.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET packetsParser APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(packetsParser SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(packetsParser
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(packetsParser PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.packetsParser)
endif()
set_target_properties(packetsParser PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS packetsParser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(packetsParser)
endif()
