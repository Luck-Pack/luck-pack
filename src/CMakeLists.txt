set(INCLUDE_DIRS
  src/ui/Breadcrumbs
  src/ui/Section
  src/ui/components/section
  src/managers/file_repository
  PARENT_SCOPE
)

set(UI_SOURCES
  src/ui/Section/SectionModel.hpp
  src/ui/Section/SectionModel.cpp
  src/ui/Breadcrumbs/BreadcrumbsModel.hpp
  src/ui/Breadcrumbs/BreadcrumbsModel.cpp
  src/ui/components/section/section.hpp
  src/ui/components/section/section.cpp
  PARENT_SCOPE
)

set(MANAGER_SOURCES
  src/managers/file_repository/file_repository.hpp
  src/managers/file_repository/file_repository.cpp
  PARENT_SCOPE
)

set(QML_SOURCES
  src/Main.qml
  src/ui/base/GridModelView.qml
  src/ui/Breadcrumbs/BreadcrumbsView.qml
  src/ui/Section/SectionView.qml
  src/ui/js/event_utils.js
  PARENT_SCOPE
)