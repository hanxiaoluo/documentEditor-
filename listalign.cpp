#include "listalign.h"
#include "ui_listalign.h"

listAlign::listAlign(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent,flags),
    ui(new Ui::listAlign)
{
    ui->setupUi(this);

    QFont f( "ZYSong18030", 12 );
    setFont( f );

    setWindowTitle( tr( "List&Alignment" ) );

    QToolBar * pToolBar = addToolBar( "List" );
    pLabel = new QLabel( tr( "List:" ) );
    pListBox = new QComboBox( pToolBar );
    pListBox->addItem( tr( "Standard" ) );
    pListBox->addItem( tr( "Bullet List (Disc)" ) );
    pListBox->addItem( tr( "Bullet List (Circle)" ) );
    pListBox->addItem( tr( "Bullet List (Square)" ) );
    pListBox->addItem( tr( "Ordered List (Decimal)" ) );
    pListBox->addItem( tr( "Ordered List (Alpha lower)" ) );
    pListBox->addItem( tr( "Ordered List (Alpha upper)" ) );
    pToolBar->addWidget( pLabel );
    pToolBar->addWidget( pListBox );

    pToolBar->addSeparator();

    QActionGroup * pActGrp = new QActionGroup( this );
    pLeftAction = new QAction( QIcon( ".//Resources//left.png" ), tr( "left" ), pActGrp );
    pLeftAction->setCheckable( true );

    pCenterAction = new QAction( QIcon( ".//Resources//center.png" ), tr( "center" ), pActGrp );
    pCenterAction->setCheckable( true );

    pJustifyAction = new QAction( QIcon( ".//Resources//justify.png" ), tr( "justify" ), pActGrp );
    pJustifyAction->setCheckable( true );

    pRightAction = new QAction( QIcon( ".//Resources//right.png" ), tr( "right" ), pActGrp );
    pRightAction->setCheckable( true );

    pToolBar->addActions( pActGrp->actions() );

    QToolBar * pEditBar = addToolBar( "Edit" );
    pUndoAction = new QAction( QIcon( ".//Resources//undo.png" ), tr( "undo" ), this );
    pEditBar->addAction( pUndoAction );
    pRedoAction = new QAction( QIcon( ".//Resources//redo.png" ), tr( "redo" ), this );
    pEditBar->addAction( pRedoAction );

    pText = new QTextEdit( this );
    pText->setFocus();
    setCentralWidget( pText );

    connect( pListBox, SIGNAL( activated( int) ), this, SLOT( slotList( int ) ) );
    connect( pActGrp, SIGNAL( triggered( QAction * ) ), this, SLOT( slotAlignment( QAction * ) ) );
    connect( pRedoAction, SIGNAL( triggered() ), pText, SLOT( redo() ) );
    connect( pUndoAction, SIGNAL( triggered() ), pText, SLOT( undo() ) );
    connect( pText->document(), SIGNAL( redoAvailable( bool ) ), pRedoAction, SLOT( setEnabled( bool ) ) );
    connect( pText->document(), SIGNAL( undoAvailable( bool ) ), pUndoAction, SLOT( setEnabled( bool ) ) );
    connect( pText, SIGNAL( cursorPositionChanged() ), this, SLOT( slotCursorPositionChanged() ) );
}

void listAlign::slotAlignment( QAction * act )
{
       if ( act == pLeftAction )
              pText->setAlignment( Qt::AlignLeft );
       if ( act == pCenterAction )
              pText->setAlignment( Qt::AlignCenter );
       if ( act == pJustifyAction )
              pText->setAlignment( Qt::AlignJustify );
       if ( act == pRightAction )
              pText->setAlignment( Qt::AlignRight );

}

void listAlign::slotList( int index )
{
       QTextCursor cursor = pText->textCursor();

       if ( index != 0 )
       {
              QTextListFormat::Style style = QTextListFormat::ListDisc;

              switch ( index )
              {
                     default:
                     case 1:
                            style = QTextListFormat::ListDisc;
                            break;
                     case 2:
                            style = QTextListFormat::ListCircle;
                            break;
                     case 3:
                            style = QTextListFormat::ListSquare;
                            break;
                     case 4:
                            style = QTextListFormat::ListDecimal;
                            break;
                     case 5:
                            style = QTextListFormat::ListLowerAlpha;
                            break;
                     case 6:
                            style = QTextListFormat::ListUpperAlpha;
                            break;
              }

              cursor.beginEditBlock();
              QTextBlockFormat blockFmt = cursor.blockFormat();
              QTextListFormat listFmt;

              if ( cursor.currentList() )
              {
                     //listFmt = cursor.currentList()->format();

                     //QTextList *textlist = cursor.currentList();
              }
              else
              {
                     listFmt.setIndent( blockFmt.indent() + 1 );
                     blockFmt.setIndent( 0 );
                     cursor.setBlockFormat( blockFmt );
              }
              listFmt.setStyle( style );
              cursor.createList( listFmt );
              cursor.endEditBlock();
       }
       else
       {
               QTextBlockFormat bfmt;
         bfmt.setObjectIndex( -1 );
         cursor.mergeBlockFormat( bfmt );
       }
}

void listAlign::slotCursorPositionChanged()
{
       if ( pText->alignment() == Qt::AlignLeft)
          pLeftAction->setChecked(true);
    if (pText->alignment() == Qt::AlignCenter)
          pCenterAction->setChecked(true);
    if (pText->alignment() == Qt::AlignJustify)
          pJustifyAction->setChecked(true);
    if (pText->alignment() == Qt::AlignRight)
          pRightAction->setChecked(true);
}

listAlign::~listAlign()
{
    delete ui;
}
