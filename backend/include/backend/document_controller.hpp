#ifndef DOCUMENT_CONTROLLER_HPP
#define DOCUMENT_CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QThread>
#include <QFileDialog>

namespace backend {

class DocumentController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY documentChanged)
    Q_PROPERTY(QString content READ content NOTIFY contentChanged)
    Q_PROPERTY(QString currentPath READ currentPath NOTIFY currentPathChanged)

public:
    explicit DocumentController(QObject* parent = nullptr);
    
    Q_INVOKABLE void openFile(const QString& path);
    Q_INVOKABLE void selectFile();
    
    
    QString title() const;
    QString content() const;
    QString currentPath() const { return m_currentPath; }

signals:
    void documentChanged();
    void contentChanged();  // New signal for real-time updates
    void currentPathChanged();

private:
    void displayContentStaggered(const QString& fullContent);
    
    QString m_title;
    QString m_content;
    QString m_currentPath;
};

} // namespace backend

#endif // DOCUMENT_CONTROLLER_HPP