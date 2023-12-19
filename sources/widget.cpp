#include "epubdocument.h"
#include "widget.h"

#include <QFileDialog>
#include <QSettings>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QAbstractTextDocumentLayout>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QDialog(parent),
    m_document(new EPubDocument(this)),
    m_currentChapter(0)
{
    setWindowFlags(Qt::Dialog);
    resize(600, 800);
    m_document->setParent(this);

    connect(m_document, &EPubDocument::loadCompleted, this, [&]() {
        update();
    });
}

Widget::~Widget()
{

}

bool Widget::loadFile(const QString &path, const QString bookName)
{
    if (path.isEmpty()) {
        return false;
    }

    if (!QFile::exists(path)) {
        qWarning() << path << "doesn't exist";
        return false;
    }
    this->setWindowTitle(bookName);
    m_document->setPageSize(size());

    m_document->openDocument(path);

    return true;
}

void Widget::scroll(int amount)
{
    int offset = m_yOffset + amount;
    offset = qMin(int(m_document->size().height() - m_document->pageSize().height()), offset);
    m_yOffset = qMax(0, offset);
    update();
}

void Widget::scrollPage(int amount)
{
    int currentPage = m_yOffset / m_document->pageSize().height();
    currentPage += amount;
    int offset = currentPage * m_document->pageSize().height();
    offset = qMin(int(m_document->size().height() - m_document->pageSize().height()), offset);
    m_yOffset = qMax(0, offset);
    update();
}

void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    if (!m_document->loaded()) {
        painter.drawText(rect(), Qt::AlignCenter, "Loading...");
        return;
    }

    QAbstractTextDocumentLayout::PaintContext paintContext;
    paintContext.clip = rect();
    paintContext.clip.translate(0, m_yOffset);

    paintContext.palette = palette();
    for (int group = 0; group < 3; ++group) {
        paintContext.palette.setColor(QPalette::ColorGroup(group), QPalette::WindowText, Qt::black);
        paintContext.palette.setColor(QPalette::ColorGroup(group), QPalette::Light, Qt::black);
        paintContext.palette.setColor(QPalette::ColorGroup(group), QPalette::Text, Qt::black);
        paintContext.palette.setColor(QPalette::ColorGroup(group), QPalette::Base, Qt::black);

        paintContext.palette.setColor(QPalette::ColorGroup(group), QPalette::Base, Qt::white);
        paintContext.palette.setColor(QPalette::ColorGroup(group), QPalette::Window, Qt::white);
        paintContext.palette.setColor(QPalette::ColorGroup(group), QPalette::Button, Qt::white);
    }

    painter.translate(0, -m_yOffset);
    painter.setClipRect(paintContext.clip);
    m_document->documentLayout()->draw(&painter, paintContext);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        scroll(-50);
    } else if (event->key() == Qt::Key_Down) {
        scroll(50);
    } else if (event->key() == Qt::Key_Left) {
        scrollPage(-1);
    } else if (event->key() == Qt::Key_Right) {
        scrollPage(1);
    } else if (event->key() == Qt::Key_End) {
        m_yOffset = m_document->size().height() - m_document->pageSize().height();
        update();
    } else if (event->key() == Qt::Key_Escape) {
        close();
    }
}

void Widget::resizeEvent(QResizeEvent *)
{
    m_document->clearCache();
    m_document->setPageSize(size());
    update();
}

