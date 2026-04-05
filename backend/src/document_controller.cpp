#include "backend/document_controller.hpp"
#include "core/parser.hpp"

#include <QCoreApplication>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>
#include <QThread>
#include <QRegularExpression>

namespace backend {

DocumentController::DocumentController(QObject* parent)
    : QObject(parent) {}

void DocumentController::openFile(const QString& path)
{
    QString resolvedPath = path;

    // Handle file URLs (from Qt.labs.platform.FileDialog)
    QUrl url(path);
    if (url.isValid() && url.isLocalFile()) {
        resolvedPath = url.toLocalFile();
    }

    // Resolve relative paths against the executable directory
    QFileInfo fileInfo(resolvedPath);
    if (fileInfo.isRelative()) {
        resolvedPath =
            QCoreApplication::applicationDirPath() + "/" + resolvedPath;
        fileInfo.setFile(resolvedPath);
    }

    // Check existence BEFORE parsing
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        qWarning() << "File does not exist:" << fileInfo.absoluteFilePath();
        return;
    }

    try {
        core::Parser parser;
        auto doc = parser.parse(fileInfo.absoluteFilePath().toStdString());

        m_title = QString::fromStdString(doc.title);
        emit documentChanged();

        // Display content with staggered effect
        QString fullContent = QString::fromStdString(doc.content);
        displayContentStaggered(fullContent);
    }
    catch (const std::exception& e) {
        qWarning() << "Parser error:" << e.what();
    }
}

void DocumentController::displayContentStaggered(const QString& fullContent)
{
    QStringList words = fullContent.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    
    for (const QString& word : words) {
        m_content = word;
        emit contentChanged();  // Notify QML immediately
        
        QThread::msleep(100);  // Wait 100ms
        QCoreApplication::processEvents();  // Process Qt events to update UI
    }
}

void DocumentController::selectFile() {
    // Opens the native Windows File Explorer dialog
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        tr("Open PDF"),
        "", 
        tr("PDF Files (*.pdf);;All Files (*)")
    );

    if (!fileName.isEmpty()) {
        m_currentPath = fileName;
        emit currentPathChanged();
        
        // Automatically start processing the file
        openFile(fileName);
    }
}

QString DocumentController::title() const {
    return m_title;
}

QString DocumentController::content() const {
    return m_content;
}

} // namespace backend