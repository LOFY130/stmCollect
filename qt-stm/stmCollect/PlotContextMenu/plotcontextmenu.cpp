#include "plotcontextmenu.h"

PlotContextMenu::PlotContextMenu(QCustomPlot* plotWidget, QObject* parent)
    : QObject(parent), m_plotWidget(plotWidget), crosshair1Enabled(false)
{
    if (m_plotWidget) {
        m_plotWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(m_plotWidget, &QCustomPlot::customContextMenuRequested,this, &PlotContextMenu::handleContextMenuRequest);
        // 初始化十字光标线
        v1Line = new QCPItemStraightLine(m_plotWidget);
        h1Line = new QCPItemStraightLine(m_plotWidget);
        v1Line->setPen(QPen(Qt::red, 1, Qt::DashLine));
        h1Line->setPen(QPen(Qt::red, 1, Qt::DashLine));
        v1Line->setVisible(false);
        h1Line->setVisible(false);

        cursorText1 = new QCPItemText(m_plotWidget);
        cursorText1->setLayer("overlay");
        cursorText1->setPositionAlignment(Qt::AlignLeft | Qt::AlignTop);
        cursorText1->position->setType(QCPItemPosition::ptPlotCoords);
        cursorText1->setText("");
        cursorText1->setPen(QPen(Qt::black));
        cursorText1->setPadding(QMargins(3, 3, 3, 3));
        cursorText1->setVisible(false);
    }
}

void PlotContextMenu::handleContextMenuRequest(const QPoint &pos)
{
    if (!m_plotWidget) return;

       QMenu contextMenu;

       QAction *savePng = contextMenu.addAction("保存为图片");
       QAction *clearPlot = contextMenu.addAction("清除图像");
       QAction *copyPlot = contextMenu.addAction("复制到剪贴板");
       contextMenu.addSeparator();

       QAction *toggleCrosshair = contextMenu.addAction("显示/隐藏十字光标");
       toggleCrosshair->setCheckable(true);
       toggleCrosshair->setChecked(crosshair1Enabled);  // 初始状态绑定变量

       QAction *selectedAction = contextMenu.exec(m_plotWidget->mapToGlobal(pos));

       if (selectedAction == savePng) {
           QString fileName = QFileDialog::getSaveFileName(m_plotWidget,
               "保存图片", "", "PNG图像 (*.png)");
           if (!fileName.isEmpty()) {
               m_plotWidget->savePng(fileName);
           }
       } else if (selectedAction == clearPlot) {
           for (int i = 0; i < m_plotWidget->graphCount(); ++i) {
               m_plotWidget->graph(i)->data()->clear();
           }
           m_plotWidget->replot();
       } else if (selectedAction == copyPlot) {
           QPixmap pix = m_plotWidget->toPixmap();
           QApplication::clipboard()->setPixmap(pix);
       }else if (selectedAction == toggleCrosshair) {
           toggleCrosshairVisibility(!crosshair1Enabled); // 切换十字光标状态
       }
}

void PlotContextMenu::onsyMouseMove(QMouseEvent *event)
{
    if (!crosshair1Enabled) {
        v1Line->setVisible(false);
        h1Line->setVisible(false);
        cursorText1->setVisible(false);
        m_plotWidget->replot(QCustomPlot::rpQueuedReplot);
        return;
    }

    double x = m_plotWidget->xAxis->pixelToCoord(event->pos().x());
    double y = m_plotWidget->yAxis->pixelToCoord(event->pos().y());

    v1Line->point1->setCoords(x, 0);
    v1Line->point2->setCoords(x, 1);
    h1Line->point1->setCoords(0, y);
    h1Line->point2->setCoords(1, y);
    v1Line->setVisible(true);
    h1Line->setVisible(true);

    cursorText1->position->setCoords(x, y);
    cursorText1->setText(QString("x: %1\ny: %2").arg(x, 0, 'f', 2).arg(y, 0, 'f', 2));
    cursorText1->setVisible(true);

    m_plotWidget->replot(QCustomPlot::rpQueuedReplot);
}

void PlotContextMenu::toggleCrosshairVisibility(bool enable)
{
    crosshair1Enabled = enable;

    if (!crosshair1Enabled) {
        v1Line->setVisible(false);
        h1Line->setVisible(false);
        cursorText1->setVisible(false);
    }
    m_plotWidget->replot(QCustomPlot::rpQueuedReplot);
}
