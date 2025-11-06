#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent, f) {setCursor(Qt::PointingHandCursor);}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QLabel::mousePressEvent(event);
}

void configureImageLabel(QLabel* label, const QString& imagePath)
{
    label->setScaledContents(true);
    label->setMinimumSize(100, 50);
    //label->setMaximumSize(600, 300);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setAlignment(Qt::AlignCenter);

    // specific management for clickable labels
    if (!imagePath.isEmpty())
    {
        if (auto clickable = qobject_cast<ClickableLabel*>(label))
        {
            clickable->setImage(imagePath);
            clickable->setCursor(Qt::PointingHandCursor);
        }
        else
        {
            QPixmap pixmap(imagePath);
            if (!pixmap.isNull()) {label->setPixmap(pixmap);}
        }
    }
}
