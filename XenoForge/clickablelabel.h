#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <Qt>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();
    void setImage(const QString& path)
    {
        QPixmap pix(path);
        if(!pix.isNull()) {this->setPixmap(pix);}
    }

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

void configureImageLabel(QLabel* label, const QString& imagePath = "");

#endif // CLICKABLELABEL_H
