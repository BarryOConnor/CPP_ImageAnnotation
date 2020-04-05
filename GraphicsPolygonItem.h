#ifndef CUSTOMPOLYGON_H
#define CUSTOMPOLYGON_H
#include "Annotation.h"

#include <QGraphicsPolygonItem>

class GraphicsScene;

class GraphicsPolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

public:

    GraphicsPolygonItem(QPolygonF varPolygon, QString varLabel, int varId, int varShape, int varColor, QMenu *varPopupMenu, GraphicsScene *varParent);
    GraphicsPolygonItem(Annotation *varAnnotation, QMenu *varPopupMenu, GraphicsScene *varParent);
    int getId();
    int getColor();
    QString getLabel();
    QPolygonF getPolygon() const;
    void paint(QPainter *varPainter, const QStyleOptionGraphicsItem *varOption, QWidget *varWidget) override;
    QVariant itemChange(GraphicsItemChange varChange, const QVariant &varValue) override;

    QPainterPath shape() const override;

signals:
    void itemMoved(int varId);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *varEvent) override;

private:
    QMenu * popupMenu;
    std::vector<QPointF> m_points;
    QString label;
    int color;
    int id;
    int shapetype;
};

#endif // CUSTOMPOLYGON_H
