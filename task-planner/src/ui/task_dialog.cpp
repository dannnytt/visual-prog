#include "task_dialog.h"

TaskDialog::TaskDialog(QWidget *parent) : QDialog(parent) {

    setMinimumSize(600, 900);
    mainLayout = new QVBoxLayout(this);
    setupTitlePart();
    setupGroupPart();
    setupDatePart();
    setupPriorityPart();
    setupSubtasksPart();

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainLayout->addSpacerItem(spacer);

    QHBoxLayout *dialogButtonLayout = new QHBoxLayout();
    saveButton = new QPushButton(tr("Сохранить"), this);
    cancelButton = new QPushButton(tr("Отменить"), this);
    dialogButtonLayout->addWidget(cancelButton);
    dialogButtonLayout->addWidget(saveButton);
    mainLayout->addLayout(dialogButtonLayout);


    connect(saveButton, &QPushButton::clicked, this, &TaskDialog::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &TaskDialog::onCancelClicked);
}

void TaskDialog::setupTitlePart() {
    taskTitleInput = new QLineEdit(this);
    taskTitleInput->setPlaceholderText(tr("Название задачи"));

    QVBoxLayout *taskTitleLayout = new QVBoxLayout();
    taskTitleLayout->addWidget(new QLabel(tr("Название задачи:")));
    taskTitleLayout->addWidget(taskTitleInput);
    mainLayout->addLayout(taskTitleLayout);
}

void TaskDialog::setupGroupPart() {
    QVBoxLayout *groupLayout = new QVBoxLayout();
    groupLayout->addWidget(new QLabel(tr("Тема задачи:")));

    groupComboBox = new QComboBox(this); // Используем QComboBox для выбора группы
    groupComboBox->setEditable(true);   // Даем возможность добавлять свою группу
    groupComboBox->addItems({"Работа", "Учеба", "Дом", "Спорт", "Другое"}); // Пример значений
    groupLayout->addWidget(groupComboBox);

    mainLayout->addLayout(groupLayout);
}


void TaskDialog::setupDatePart() {
    QVBoxLayout *dateLayout = new QVBoxLayout();
    dateLayout->addWidget(new QLabel(tr("Дедлайн:")));

    dateEdit = new QDateEdit(this);
    dateEdit->setDisplayFormat("dd.MM.yyyy");
    dateLayout->addWidget(dateEdit);

    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setGridVisible(true);
    dateLayout->addWidget(calendarWidget);
    mainLayout->addLayout(dateLayout);
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &TaskDialog::onCalendarDateChanged);
}

void TaskDialog::setupPriorityPart() {
    lowPriorityRadio = new QRadioButton(tr("Низкий"), this);
    mediumPriorityRadio = new QRadioButton(tr("Средний"), this);
    highPriorityRadio = new QRadioButton(tr("Высокий"), this);
    lowPriorityRadio->setChecked(true); // По умолчанию

    QGroupBox *priorityGroupBox = new QGroupBox(tr("Выбор приоритета:"), this);
    QVBoxLayout *priorityLayout = new QVBoxLayout(priorityGroupBox);

    priorityLayout->addWidget(lowPriorityRadio);
    priorityLayout->addWidget(mediumPriorityRadio);
    priorityLayout->addWidget(highPriorityRadio);

    mainLayout->addWidget(priorityGroupBox);
}


void TaskDialog::setupSubtasksPart() {
    addSubtaskButton = new QPushButton(tr("Добавить подзадачу"), this);
    removeSubtaskButton = new QPushButton(tr("Удалить подзадачу"), this);

    subtasksListWidget = new QListWidget(this);
    mainLayout->addWidget(new QLabel(tr("Подзадачи:")));
    mainLayout->addWidget(subtasksListWidget);

    QHBoxLayout *subtasksButtonLayout = new QHBoxLayout();
    subtasksButtonLayout->addWidget(removeSubtaskButton);
    subtasksButtonLayout->addWidget(addSubtaskButton);
    mainLayout->addLayout(subtasksButtonLayout);

    connect(addSubtaskButton, &QPushButton::clicked, this, &TaskDialog::addSubtask);
    connect(removeSubtaskButton, &QPushButton::clicked, this, &TaskDialog::removeSubtask);
}

void TaskDialog::addSubtask() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Добавить подзадачу"),
                                         tr("Введите название подзадачи:"), QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        subtasksListWidget->addItem(text);
    }
}

void TaskDialog::removeSubtask() {
    QListWidgetItem *selectedItem = subtasksListWidget->currentItem();
    if (selectedItem) {
        delete subtasksListWidget->takeItem(subtasksListWidget->row(selectedItem));
    }
}

QString TaskDialog::getName() const {
    return taskTitleInput->text();
}

void TaskDialog::setName(const QString &name) {
    taskTitleInput->setText(name);
}

QString TaskDialog::getGroup() const {
    return groupComboBox->currentText();
}

void TaskDialog::setGroup(const QString &group) {
    groupComboBox->setCurrentText(group);
}

QDate TaskDialog::getDeadline() const {
    return dateEdit->date();
}

void TaskDialog::setDeadline(const QDate &deadline) {
    dateEdit->setDate(deadline);
}

int TaskDialog::getPriority() const {
    if (lowPriorityRadio->isChecked()) return 1;
    if (mediumPriorityRadio->isChecked()) return 2;
    if (highPriorityRadio->isChecked()) return 3;
    return -1;
}

void TaskDialog::setPriority(int priority) {
    switch (priority) {
    case 1:
        lowPriorityRadio->setChecked(true);
        break;
    case 2:
        mediumPriorityRadio->setChecked(true);
        break;
    case 3:
        highPriorityRadio->setChecked(true);
        break;
    default:
        break;
    }
}

QStringList TaskDialog::getSubtasks() const {
    QStringList subtasks;
    for (int i = 0; i < subtasksListWidget->count(); ++i) {
        subtasks << subtasksListWidget->item(i)->text();
    }
    return subtasks;
}

void TaskDialog::setSubtasks(const QStringList &subtasks) {
    subtasksListWidget->clear();
    for (const QString &subtask : subtasks) {
        subtasksListWidget->addItem(subtask);
    }
}

void TaskDialog::onSaveClicked() {
    accept();
}

void TaskDialog::onCancelClicked() {
    reject();
}

void TaskDialog::onCalendarDateChanged() {
    dateEdit->setDate(calendarWidget->selectedDate());
}
