#ifndef CDEBUG_H
#define CDEBUG_H

#include <QDialog>

namespace Ui {
class CDebug;
}

class CDebug : public QDialog
{
    Q_OBJECT

public:
    explicit CDebug(QWidget *parent = nullptr);
    ~CDebug();


    void PutLog(const QString&log);


private slots:
    void on_pb_clearLwDebug_clicked();

    void reject() override {}

private:
    Ui::CDebug *ui;
};

#endif // CDEBUG_H
