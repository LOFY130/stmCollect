#ifndef PLOTCONTEXTMENU_H
#define PLOTCONTEXTMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QApplication>
#include <QClipboard>
#include "qcustomplot/qcustomplot.h"

class PlotContextMenu : public QObject
{
    Q_OBJECT
public:
    explicit PlotContextMenu(QCustomPlot* plotWidget, QObject* parent = nullptr);

    void handleContextMenuRequest(const QPoint &pos) ;
    void onsyMouseMove(QMouseEvent *event) ;
    void toggleCrosshairVisibility(bool enable);

private:
    QCustomPlot* m_plotWidget;
    bool crosshair1Enabled;
    QCPItemStraightLine *v1Line;
    QCPItemStraightLine *h1Line;
    QCPItemText *cursorText1;
};


#endif // PLOTCONTEXTMENU_H
