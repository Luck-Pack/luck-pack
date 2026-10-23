#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include "src/managers/file_repository/file_repository.hpp"
#include "src/ui/Section/SectionModel.hpp"
#include "src/ui/Breadcrumbs/BreadcrumbsModel.hpp"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  FileRepository fileRepository{};
  SectionModel sectionModel{};
  BreadcrumbsModel breadcrumbsModel{};

  qmlRegisterSingletonInstance("LuckPack", 1, 0, "SectionModel", &sectionModel);
  qmlRegisterSingletonInstance("LuckPack", 1, 0, "BreadcrumbsModel", &breadcrumbsModel);
  qmlRegisterSingletonInstance("LuckPack", 1, 0, "FileRepository", &fileRepository);

  engine.loadFromModule("LuckPack", "Main");
  fileRepository.openStorage("../../data");

  return app.exec();
}