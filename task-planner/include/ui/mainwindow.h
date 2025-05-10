#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QSplitter>
#include <QListWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QInputDialog>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>


#include "task_dialog.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void setupLeftPart();
    void setupMiddlePart();
    void setupRightPart();

    void setupDatabase();
    void saveTasksToDatabase();
    void loadTasksFromDatabase();

    void addTask();
    void removeTask();
    void removeCompletedTask(QListWidgetItem *item);
    void editTask(QListWidgetItem *item);
    void completeTask(QListWidgetItem *item);
    void showTaskDetails(int index);
    QString priorityToString(int priority);

    void closeEvent(QCloseEvent *event);

    void checkTaskDeadlines();
    void showNotification(const QString &taskName);

    QWidget *centralWidget;
    QSplitter *splitter;
    // Средняя часть
    QListWidget *taskList;
    QListWidget *completedTaskList;
    QTextEdit *descriptionInput;
    QDateEdit *dateInput;
    QTimeEdit *timeInput;
    QPushButton *addTaskButton;
    QPushButton *removeTaskButton;
    QPushButton *editTaskButton;

    // Правая часть
    QLabel *nameLabel;
    QLabel *themeLabel;
    QLabel *deadlineLabel;
    QLabel *priorityLabel;
    QListWidget *subtasksListWidget;

};

#endif // MAINWINDOW_H
