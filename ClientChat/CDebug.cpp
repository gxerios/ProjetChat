#include "CDebug.h"
#include "ui_CDebug.h"

CDebug::CDebug(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDebug)
{
    ui->setupUi(this);
    connect(
         ui->lw_debug->model(),
         SIGNAL(rowsInserted(QModelIndex,int,int)),
         ui->lw_debug,
         SLOT(scrollToBottom()));
}

CDebug::~CDebug(){
    delete ui;
}

void CDebug::on_pb_clearLwDebug_clicked(){
    ui->lw_debug->clear();
}

void CDebug::PutLog(const QString&log){
    ui->lw_debug->addItem(log);
}
