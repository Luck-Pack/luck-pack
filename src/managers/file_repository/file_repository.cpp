#include <QFileInfo>
#include <vector>
#include <QDir>
#include "file_repository.hpp"

namespace {
  QList<Node> createNodeList(const QString& path) {
    QDir files{path};

    QFileInfoList entries = files.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    if (entries.empty()) entries = files.entryInfoList(QDir::Files);

    QList<Node> list{};
    list.reserve(entries.size());

    for (const QFileInfo& entry : entries) {
      list.emplace_back(entry.absoluteFilePath());
    }
    return list;
  }
}

FileRepository::FileRepository(QObject *parent) : QObject{parent} {}

void FileRepository::openStorage(const QString& path) {
  Section::Mode mode{}; // TODO

  m_rootSection = std::make_unique<Section>(path, createNodeList(path), mode);
  emit rootSectionChanged(m_rootSection.get());
}

void FileRepository::openNextSection(Section* currentSection, Node* node) {
  Section::Mode mode{}; // TODO

  m_sections.emplace_back(std::make_unique<Section>(
    node->path(),
    createNodeList(node->path()),
    mode,
    currentSection
  ));

  node->setNextSection(m_sections.back().get());
  emit nextSectionOpened();
}