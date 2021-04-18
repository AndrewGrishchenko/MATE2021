#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class CustomLabel : public QLabel
{
    Q_OBJECT


public:
    CustomLabel( QWidget* parent = 0, Qt::WindowFlags f = 0 );
    CustomLabel( const QString& text, QWidget* parent = 0, Qt::WindowFlags f = 0 );

    int xpos, ypos;
    void mousePressEvent( QMouseEvent* ev );

signals:
    void mousePressed( const QPoint&);
};



//CustomLabel::CustomLabel( QWidget * parent, Qt::WindowFlags f )
//    : QLabel( parent, f ) {}

//CustomLabel::CustomLabel( const QString& text, QWidget* parent, Qt::WindowFlags f )
//    : QLabel( text, parent, f ) {}

#endif // CUSTOMLABEL_H
