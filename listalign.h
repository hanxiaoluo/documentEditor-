#ifndef LISTALIGN_H
#define LISTALIGN_H

#include <QMainWindow>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
//#include <QTextListFormat>
//#include <QTextDocument>

namespace Ui {
class listAlign;
}

class listAlign : public QMainWindow
{
    Q_OBJECT

public:
    explicit listAlign(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~listAlign();

private:
    Ui::listAlign *ui;

    QTextEdit   * pText;
    QLabel      * pLabel;
    QComboBox   * pListBox;
    QAction * pLeftAction;
    QAction * pRightAction;
    QAction * pCenterAction;
    QAction * pJustifyAction;
    QAction * pRedoAction;
    QAction * pUndoAction;

protected slots:
   void slotAlignment( QAction * );
   void slotList( int );
   void slotCursorPositionChanged();
};

#endif // LISTALIGN_H
