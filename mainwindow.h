#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>


#include "controller/uitodbtable.h"
#include "visual/routesui.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:    


private:
    RoutesUI  *ui;

    std::shared_ptr<IDataProvider> m_provider;
    std::shared_ptr<UIToDBTable > m_ui_all_rts;
    std::shared_ptr<UIToDBTable > m_ui_rt_conf;
    std::shared_ptr<UIToDBTable > m_ui_subrt_conf;


    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
};


#endif // MAINWINDOW_H
