#ifndef TASK_DIALOG_H
#define TASK_DIALOG_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QInputDialog>
#include <QCalendarWidget>
#include <QComboBox>
class TaskDialog : public QDialog {
    Q_OBJECT
public:
    explicit TaskDialog(QWidget *parent = nullptr);

    QString getName() const;
    QString getGroup() const;
    QDate getDeadline() const;
    int getPriority() const;
    QStringList getSubtasks() const;

    void setName(const QString &name);
    void setGroup(const QString &group);
    void setDeadline(const QDate &deadline);
    void setPriority(int priority);
    void setSubtasks(const QStringList &subtasks);

private:
    void setupTitlePart();
    void setupGroupPart();
    void setupDatePart();
    void setupPriorityPart();
    void setupSubtasksPart();

    QVBoxLayout *mainLayout;
    QLineEdit *taskTitleInput;
    QComboBox *groupComboBox;
    QDateEdit *dateEdit;
    QCalendarWidget *calendarWidget;
    QListWidget *subtasksListWidget;
    QPushButton *addSubtaskButton;
    QPushButton *removeSubtaskButton;
    QRadioButton *lowPriorityRadio;
    QRadioButton *mediumPriorityRadio;
    QRadioButton *highPriorityRadio;
    QButtonGroup *priorityButtonGroup;
    QPushButton *saveButton;
    QPushButton *cancelButton;

private slots:
    void onSaveClicked();
    void onCancelClicked();
    void onCalendarDateChanged();
    void addSubtask();
    void removeSubtask();
};

#endif // TASK_DIALOG_H
