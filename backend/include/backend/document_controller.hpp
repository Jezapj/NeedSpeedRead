#ifndef DOCUMENT_CONTROLLER_HPP
#define DOCUMENT_CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QThread>

namespace backend {

class DocumentController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY documentChanged)
    Q_PROPERTY(QString content READ content NOTIFY contentChanged)

public:
    explicit DocumentController(QObject* parent = nullptr);
    
    Q_INVOKABLE void openFile(const QString& path);
    
    QString title() const;
    QString content() const;

signals:
    void documentChanged();
    void contentChanged();  // New signal for real-time updates

private:
    void displayContentStaggered(const QString& fullContent);
    
    QString m_title;
    QString m_content;
};

} // namespace backend

#endif // DOCUMENT_CONTROLLER_HPP